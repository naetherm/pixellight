/*********************************************************\
 *  File: Script.cpp                                     *
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
#include <PLGeneral/Log/Log.h>
#include "PLScriptV8/Script.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLCore;
namespace PLScriptV8 {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Script)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
Script::Script()
{
}

/**
*  @brief
*    Destructor
*/
Script::~Script()
{
	// Clear the script
	Clear();

	// Remove all dynamic functions
	RemoveAllDynamicFunctions();
}


//[-------------------------------------------------------]
//[ Public virtual PLScript::Script functions             ]
//[-------------------------------------------------------]
bool Script::AddDynamicFunction(const String &sFunction, const DynFunc &cDynFunc, const String &sNamespace)
{
	// Is there a V8 context?
	if (m_cV8Context.IsEmpty()) {
		// Add the dynamic function
		DynamicFunction *psDynamicFunction = new DynamicFunction;
		psDynamicFunction->sFunction  = sFunction;
		psDynamicFunction->pDynFunc   = cDynFunc.Clone();
		psDynamicFunction->sNamespace = sNamespace;
		m_lstDynamicFunctions.Add(psDynamicFunction);

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

bool Script::RemoveAllDynamicFunctions()
{
	// Is there a V8 context?
	if (m_cV8Context.IsEmpty()) {
		// Destroy the dynamic functions
		for (uint32 i=0; i<m_lstDynamicFunctions.GetNumOfElements(); i++) {
			delete m_lstDynamicFunctions[i]->pDynFunc;
			delete m_lstDynamicFunctions[i];
		}
		m_lstDynamicFunctions.Clear();

		// Done
		return true;
	} else {
		// Error!
		return false;
	}
}

String Script::GetSourceCode() const
{
	return m_sSourceCode;
}

bool Script::SetSourceCode(const String &sSourceCode)
{
	// Clear the previous script
	Clear();

	// Backup the given source code
	m_sSourceCode = sSourceCode;

	// Is there source code?
	if (m_sSourceCode.GetLength()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Are there any dynamic functions?
		if (m_lstDynamicFunctions.GetNumOfElements()) {
			// Create a template for the global object and set the
			// built-in global functions.
			v8::Local<v8::ObjectTemplate> cV8Globals = v8::ObjectTemplate::New();

			// Add the dynamic functions
			for (uint32 i=0; i<m_lstDynamicFunctions.GetNumOfElements(); i++) {
				// Get the dynamic function
				DynamicFunction *psDynamicFunction = m_lstDynamicFunctions[i];

				// Add V8 function
				v8::Local<v8::ObjectTemplate> cV8Function = v8::ObjectTemplate::New();
				cV8Function->SetCallAsFunctionHandler(V8FunctionCallback, v8::External::New(psDynamicFunction));
				cV8Globals->Set(v8::String::New(psDynamicFunction->sFunction), cV8Function, v8::ReadOnly);
			}

			// Create a new context
			m_cV8Context = v8::Context::New(nullptr, cV8Globals);
		} else {
			// Create a new context
			m_cV8Context = v8::Context::New();
		}

		// Enter the created context for compiling and running the hello world script
		v8::Context::Scope cContextScope(m_cV8Context);

		// Create a string containing the JavaScript source code
		v8::Local<v8::String> cSource = v8::String::New(sSourceCode);
		if (cSource.IsEmpty()) {
			// Error!
			LogOutput(Log::Error, "Failed to generate string source");
		} else {
			// Compile the source code
			v8::TryCatch cTryCatch;
			v8::Local<v8::Script> cScript = v8::Script::Compile(cSource);
			if (cScript.IsEmpty()) {
				// Error!
				LogOutputTryCatch(Log::Error, "Failed to compile the script", cTryCatch);
			} else {
				// Run the script to get the result
				if (cScript->Run().IsEmpty()) {
					// Error!
					LogOutputTryCatch(Log::Error, "Failed to run the script", cTryCatch);
				}
			}
		}
	} else {
		// No script at all - done
	}

	// Done
	return true;
}

bool Script::BeginCall(const String &sFunctionName, const String &sFunctionSignature)
{
	// Is there a V8 context?
	if (!m_cV8Context.IsEmpty()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter the created context for compiling and running the hello world script
		v8::Context::Scope cContextScope(m_cV8Context);

		// Get the V8 function
		v8::Local<v8::Value> cV8Value = m_cV8Context->Global()->Get(v8::String::New(sFunctionName));
		if (cV8Value->IsFunction()) {
			// Backup the name of the current function (we may need it for error log output)
			m_sCurrentFunction = sFunctionName;

			// Clear the V8 arguments list
			m_lstArguments.Clear();
		} else {
			// Error!
			m_sCurrentFunction = "";
			LogOutput(Log::Error, "The function '" + sFunctionName + "' was not found");
		}

		// Done
		return true;
	}

	// Error!
	return false;
}

void Script::PushArgument(int nValue)
{
	if (m_sCurrentFunction.GetLength())
		m_lstArguments.Add(nValue);
}

void Script::PushArgument(uint8 nValue)
{
	if (m_sCurrentFunction.GetLength())
		m_lstArguments.Add(nValue);
}

void Script::PushArgument(uint16 nValue)
{
	if (m_sCurrentFunction.GetLength())
		m_lstArguments.Add(nValue);
}

void Script::PushArgument(uint32 nValue)
{
	if (m_sCurrentFunction.GetLength())
		m_lstArguments.Add(nValue);
}

void Script::PushArgument(float fValue)
{
	if (m_sCurrentFunction.GetLength())
		m_lstArguments.Add(fValue);
}

void Script::PushArgument(double fValue)
{
	if (m_sCurrentFunction.GetLength())
		m_lstArguments.Add(fValue);
}

bool Script::EndCall()
{
	if (m_sCurrentFunction.GetLength()) {
		// Create a stack-allocated handle scope
		v8::HandleScope cHandleScope;

		// Enter the created context for compiling and running the hello world script
		v8::Context::Scope cContextScope(m_cV8Context);

		// Get the V8 function
		v8::Local<v8::Function> cV8Function = v8::Local<v8::Function>::Cast(m_cV8Context->Global()->Get(v8::String::New(m_sCurrentFunction)));
		if (cV8Function->IsFunction()) {
			if (m_lstArguments.GetNumOfElements()) {
				v8::Local<v8::Value> *pcArguments = new v8::Local<v8::Value>[m_lstArguments.GetNumOfElements()]();
				for (uint32 i=0; i<m_lstArguments.GetNumOfElements(); i++)
					pcArguments[i] = v8::Number::New(m_lstArguments[i]);
				m_cV8CurrentResult = cV8Function->Call(m_cV8Context->Global(), m_lstArguments.GetNumOfElements(), pcArguments);
				delete [] pcArguments;
			} else {
				m_cV8CurrentResult = cV8Function->Call(m_cV8Context->Global(), 0, nullptr);
			}
		}

		// Done
		return true;
	}

	// Error!
	return false;
}

void Script::GetReturn(int &nValue)
{
	nValue = m_cV8CurrentResult->IsUint32() ? static_cast<uint8>(m_cV8CurrentResult->Uint32Value()) : 0;
}

void Script::GetReturn(uint8 &nValue)
{
	nValue = m_cV8CurrentResult->IsUint32() ? static_cast<uint8>(m_cV8CurrentResult->Uint32Value()) : 0;
}

void Script::GetReturn(uint16 &nValue)
{
	nValue = m_cV8CurrentResult->IsUint32() ? static_cast<uint16>(m_cV8CurrentResult->Uint32Value()) : 0;
}

void Script::GetReturn(uint32 &nValue)
{
	nValue = m_cV8CurrentResult->IsUint32() ? m_cV8CurrentResult->Uint32Value() : 0;
}

void Script::GetReturn(float &fValue)
{
	fValue = m_cV8CurrentResult->IsNumber() ? static_cast<float>(m_cV8CurrentResult->NumberValue()) : 0.0f;
}

void Script::GetReturn(double &fValue)
{
	fValue = m_cV8CurrentResult->IsNumber() ? m_cV8CurrentResult->NumberValue() : 0.0;
}


//[-------------------------------------------------------]
//[ Private static V8 callback functions                  ]
//[-------------------------------------------------------]
/*
*  @brief
*    V8 function callback
*/
v8::Handle<v8::Value> Script::V8FunctionCallback(const v8::Arguments &vV8Arguments)
{
	// Get the dynamic function
	DynamicFunction *psDynamicFunction = reinterpret_cast<DynamicFunction*>(v8::External::Unwrap(vV8Arguments.Data()));
	if (psDynamicFunction) {
		// V8 arguments to parameter string
		String sParams;
		for (int i=0; i<vV8Arguments.Length(); i++)
			sParams += String("Param") + i + "=\"" + *v8::String::AsciiValue(vV8Arguments[i]->ToString()) + "\" ";

		// Call the functor
		const String sReturn = psDynamicFunction->pDynFunc->CallWithReturn(sParams);

		// Process the functor return
		switch (psDynamicFunction->pDynFunc->GetReturnTypeID()) {
			case TypeBool:		return v8::Boolean::New(sReturn.GetBool());
			case TypeDouble:	return v8::Number ::New(sReturn.GetDouble());
			case TypeFloat:		return v8::Number ::New(sReturn.GetFloat());
			case TypeInt:		return v8::Integer::New(sReturn.GetInt());
			case TypeInt16:		return v8::Integer::New(sReturn.GetInt());
			case TypeInt32:		return v8::Int32  ::New(sReturn.GetInt());
			case TypeInt64:		return v8::Integer::New(sReturn.GetInt());	// [TODO] TypeInt64 is currently handled just as int
			case TypeInt8:		return v8::Integer::New(sReturn.GetInt());
			case TypeString:	return v8::String ::New(sReturn);
			case TypeUInt16:	return v8::Integer::New(sReturn.GetUInt16());
			case TypeUInt32:	return v8::Uint32 ::New(sReturn.GetUInt32());
			case TypeUInt64:	return v8::Integer::New(static_cast<uint32>(sReturn.GetUInt64()));	// [TODO] TypeUInt64 is currently handled just as int
			case TypeUInt8:		return v8::Integer::New(sReturn.GetUInt8());
			default:			return v8::Local<v8::Value>();// TypeVoid, TypeNull, TypeObjectPtr, -1
		}
	}

	// Error!
	return v8::Local<v8::Value>();
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Copy constructor
*/
Script::Script(const Script &cSource)
{
	// No implementation because the copy constructor is never used
}

/**
*  @brief
*    Copy operator
*/
Script &Script::operator =(const Script &cSource)
{
	// No implementation because the copy operator is never used
	return *this;
}

/**
*  @brief
*    Clears the script
*/
void Script::Clear()
{
	// Reset the source code
	m_sSourceCode = "";

	// Dispose the persistent context
	if (!m_cV8Context.IsEmpty())
		m_cV8Context.Dispose();

	// Reset the name of the current function
	m_sCurrentFunction = "";

	// Clear the V8 arguments list
	m_lstArguments.Clear();
}

/**
*  @brief
*    Write a string into the log
*/
bool Script::LogOutputTryCatch(uint8 nLogLevel, const String &sText, const v8::TryCatch &cTryCatch)
{
	// Get the error description
	const String sErrorDescription = cTryCatch.HasCaught() ? (String(" (Line ") + cTryCatch.Message()->GetLineNumber() + " \"" + String::FromUTF8(*v8::String::Utf8Value(cTryCatch.Exception()))) + "\")": "";

	// Call the base implementation
	return PLScript::Script::LogOutput(nLogLevel, sText + sErrorDescription);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScriptV8