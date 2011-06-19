/*********************************************************\
 *  File: PLPluginInfo.cpp                               *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Xml/Xml.h>
#include <PLGeneral/File/File.h>
#include <PLGeneral/File/Directory.h>
#include <PLGeneral/File/FileSearch.h>
#include <PLGeneral/String/RegEx.h>
#include <PLGeneral/String/Tokenizer.h>
#include "PLPluginClassInfo.h"
#include "PLPluginInfo.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
PLPluginInfo::PLPluginInfo() :
	m_bIsActive(false),
	m_bDelayed(false)
{
}

/**
*  @brief
*    Destructor
*/
PLPluginInfo::~PLPluginInfo()
{
	// Cleanup all PLPLuginClassInfo instances
	for (uint32 i=0; i<m_lstClasses.GetNumOfElements(); i++)
		delete m_lstClasses[i];
}

/**
*  @brief
*    Sets the name of the library
*/
void PLPluginInfo::SetLibraryName(const String &sLibraryName)
{
	m_cPluginPlatformInfo.SetLibraryName(sLibraryName);
}

/**
*  @brief
*    Sets a library suffix, this string is appended to the library name
*/
void PLPluginInfo::SetLibrarySuffix(const String &sLibrarySuffix)
{
	m_cPluginPlatformInfo.SetSuffixName(sLibrarySuffix);
}

/**
*  @brief
*    Sets the version of the plugin file
*/
void PLPluginInfo::SetPluginFileVersion(const String &sPluginVersion)
{
	m_sPluginFileVersion = sPluginVersion;
}

/**
*  @brief
*    Sets the PixelLight version string
*/
void PLPluginInfo::SetPLVersion(const String &sPLVersion)
{
	m_sPLVersion = sPLVersion;
}

/**
*  @brief
*    Set active flag, this flag indicates if the plugin is active or not
*/
void PLPluginInfo::SetActive(bool bIsActive)
{
	m_bIsActive = bIsActive;
}

/**
*  @brief
*    Set delayed flag, this flag indicates if delayed loading should be used for this plugin
*/
void PLPluginInfo::SetDelayed(bool bIsDelayed)
{
	m_bDelayed = bIsDelayed;
}

/**
*  @brief
*    Saves the parsed information to the given file
*/
void PLPluginInfo::Save(const String &sFilename) const
{
	XmlDocument cDocument;
	AppendInformation(cDocument);
	cDocument.Save(sFilename);
}

/**
*  @brief
*    Saves the parsed information to the given file
*/
void PLPluginInfo::Save(File &cFile) const
{
	XmlDocument cDocument;
	AppendInformation(cDocument);
	cDocument.Save(cFile);
}

/**
*  @brief
*    Parses the found header files in the given include path for pl_class..pl_class_end blocks
*/
void PLPluginInfo::ParseIncludeFiles(const String &sIncludePath)
{
	// Check if path exists and if it points to a directory
	FileObject cIncFile(sIncludePath);
	if (cIncFile.Exists() && cIncFile.IsDirectory()) {
		// Get all header files from the include directory
		Array<String> lstFiles;
		Find(lstFiles, sIncludePath, "*.h", true);

		// Parse each header file
		for (uint32 i=0; i<lstFiles.GetNumOfElements(); i++)
			ParseFile(lstFiles[i]);
	}
}

/**
*  @brief
*    Parses the given main module source file for pl_module_plugin..pl_module_end blocks
*/
bool PLPluginInfo::ParseMainModuleFile(const String &sMainModuleFilename)
{
	// Get the complete content of the file as text
	String sContent = GetContentFromFile(sMainModuleFilename);
	if (sContent.GetLength()) {
		RegEx cPLPluginModuleBlock("^\\s*(pl_module_plugin.*pl_module_end)", RegEx::Multiline | RegEx::DotAll);
		if (cPLPluginModuleBlock.Match(sContent))
			ParsePluginModuleBlock(cPLPluginModuleBlock.GetResult(0));

		// Done
		return true;
	} else {
		// Error! No/empty file
		return false;
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
PLPluginInfo::PLPluginInfo(const PLPluginInfo &cOther) :
	m_bIsActive(false),
	m_bDelayed(false)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
PLPluginInfo &PLPluginInfo::operator =(const PLPluginInfo &cOther)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Parses a single file for an pl_class..pl_class_end block
*/
void PLPluginInfo::ParseFile(const String &sFilename)
{
	// Get the complete content of the file as text
	String sContent = GetContentFromFile(sFilename);
	if (sContent.GetLength()) {
		RegEx cPLClassPLClassEndBlock("^\\s*(pl_class\\s*.*\\s*pl_class_end)", RegEx::Multiline | RegEx::DotAll);
		if (cPLClassPLClassEndBlock.Match(sContent)) {
			PLPluginClassInfo *pInfo = new PLPluginClassInfo();
			pInfo->ParsePLClassBlock(cPLClassPLClassEndBlock.GetResult(0));
			m_lstClasses.Add(pInfo);
		}
	}
}

/**
*  @brief
*    Find files in a directory tree
*/
void PLPluginInfo::Find(Array<String> &lstNames, const String &sPath, const String &sPattern, bool bRecursive) const
{
	// Open directory
	Directory cDir(sPath);

	{ // Find files
		FileSearch cSearch(cDir, sPattern);
		while (cSearch.HasNextFile())
			lstNames.Add(sPath + '/' + cSearch.GetNextFile());
	}

	// Recurse into sub-directories?
	if (bRecursive) {
		FileSearch cSearch(cDir);
		while (cSearch.HasNextFile()) {
			const String sFilename = cSearch.GetNextFile();
			const String sFile     = sPath + '/' + sFilename;
			if (FileObject(sFile).IsDirectory() && bRecursive && sFilename != '.' && sFilename != "..")
				Find(lstNames, sFile, sPattern, bRecursive);
		}
	}
}

/**
*  @brief
*    Adds an XmlTextElement child to an XmlElement
*/
void PLPluginInfo::AddTextXmlElement(XmlElement &cParent, const String &sName, const String &sValue) const
{
	XmlElement *pElement = new XmlElement(sName);
	XmlText *pTextValue = new XmlText(sValue);
	pElement->LinkEndChild(*pTextValue);
	cParent.LinkEndChild(*pElement);
}

/**
*  @brief
*    Parses an pl_module_plugin..pl_module_end block
*/
void PLPluginInfo::ParsePluginModuleBlock(const String &sPluginModuleBlock)
{
	// Setup regular expressions
	RegEx cRegExModulePlugin("^\\s*pl_module_plugin\\(\\s*\\\"(?<name>\\w*)\\\"\\s*\\)\\s*$");
	RegEx cRegExVendor("^\\s*pl_module_vendor\\s*\\(\\s*\\\"(?<text>.*)\\\"\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExLicense("^\\s*pl_module_license\\s*\\(\\s*\\\"(?<text>.*)\\\"\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExDescription("^\\s*pl_module_description\\s*\\(\\s*\\\"(?<text>.*)\\\"\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExVersion("^\\s*pl_module_version\\s*\\(\\s*\\\"(?<text>.*)\\\"\\s*\\)\\s*$", RegEx::MatchCaseSensitive);
	RegEx cRegExActive("^\\s*pl_module_active\\s*\\((?<num>\\d)\\)\\s*$");
	RegEx cRegExDelayed("^\\s*pl_module_delayed\\s*\\((?<num>\\d)\\)\\s*$");

	// Setup tokenizer
	Tokenizer cTokenizer;
	cTokenizer.SetDelimiters("\r\n");
	cTokenizer.SetSingleChars("");
	cTokenizer.SetQuotes("");
	cTokenizer.SetCommentStartTag("");
	cTokenizer.SetCommentEndTag("");
	cTokenizer.SetSingleLineComment("");
	cTokenizer.Start(sPluginModuleBlock);

	// Iterate through all lines
	String sLine = cTokenizer.GetNextToken();
	while (sLine.GetLength()) {
		// Check for pl_module_plugin
		if (cRegExModulePlugin.Match(sLine)) {
			m_sPluginName = cRegExModulePlugin.GetNameResult("name");

		// Check for pl_module_vendor
		} else if (cRegExVendor.Match(sLine)) {
			m_sVendor = cRegExVendor.GetNameResult("text");

		// Check for pl_module_license
		} else if (cRegExLicense.Match(sLine)) {
			m_sLicense = cRegExLicense.GetNameResult("text");

		// Check for pl_module_description
		} else if (cRegExDescription.Match(sLine)) {
			m_sDescription = cRegExDescription.GetNameResult("text");

		// Check for pl_module_version
		} else if (cRegExVersion.Match(sLine)) {
			m_sModuleVersion = cRegExVersion.GetNameResult("text");

		// Let PLPluginPlatformInfo parse the line
		} else {
			m_cPluginPlatformInfo.ParseLine(sLine);
		}

		// Next, please
		sLine = cTokenizer.GetNextToken();
	}
}

/**
* @brief
*   Returns the complete content of a file as text
*/
String PLPluginInfo::GetContentFromFile(const String &sFilename) const
{
	File cFile(sFilename);
	return cFile.Open(File::FileRead | File::FileText) ? cFile.GetContentAsString() : "";
}

/**
*  @brief
*    Appends the parsed information about a plugin to the given XML document
*/
void PLPluginInfo::AppendInformation(XmlDocument &cDocument) const
{
	// Add declaration
	XmlDeclaration *pDeclaration = new XmlDeclaration("1.0", "", "");
	cDocument.LinkEndChild(*pDeclaration);
	XmlElement *pRootElement = new XmlElement("Plugin");
	pRootElement->SetAttribute("Version", m_sPluginFileVersion);
	pRootElement->SetAttribute("PixelLightVersion", m_sPLVersion);

	AddTextXmlElement(*pRootElement, "Active", m_bIsActive ? "1" : "0");
	AddTextXmlElement(*pRootElement, "Delayed", m_bDelayed ? "1" : "0");
	AddTextXmlElement(*pRootElement, "Name", m_sPluginName);
	if (m_sModuleVersion.GetLength())
		AddTextXmlElement(*pRootElement, "Version", m_sModuleVersion);
	if (m_sVendor.GetLength())
		AddTextXmlElement(*pRootElement, "Vendor", m_sVendor);
	if (m_sLicense.GetLength())
		AddTextXmlElement(*pRootElement, "License", m_sLicense);
	if (m_sDescription.GetLength())
		AddTextXmlElement(*pRootElement, "Description", m_sDescription);

	cDocument.LinkEndChild(*pRootElement);

	// Append the parsed information to the given XML element
	m_cPluginPlatformInfo.Save(*pRootElement);

	// Are there any classes?
	if (!m_lstClasses.IsEmpty()) {
		// Create the classes XML element instance
		XmlElement *pClassesElement = new XmlElement("Classes");

		// Iterate through all classes
		ConstIterator<PLPluginClassInfo*> cIterator = m_lstClasses.GetConstIterator();
		while (cIterator.HasNext())
			cIterator.Next()->Save(*pClassesElement);

		// Link the classes XML element instance to the XML root element
		pRootElement->LinkEndChild(*pClassesElement);
	}
}