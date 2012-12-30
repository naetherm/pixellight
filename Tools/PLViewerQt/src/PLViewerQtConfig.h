/*********************************************************\
 *  File: Config.h                                       *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the �Software�), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED �AS IS�, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __CONFIG_H__
#define __CONFIG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Config/Config.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    PLViewerQt configuration classes
*/
class PLViewerQtConfig : public PLCore::ConfigGroup {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, PLViewerQtConfig, "", PLCore::ConfigGroup, "PLViewerQt general configuration classes")
		// Attributes
		pl_attribute(ShowColorGradientBackground,	bool,	true,	ReadWrite,	GetSet,	"Show color gradient background? (whether or not this has an effect depends on the used scene renderer)",	"")
		pl_attribute(ShowBackfacesAndSilhouettes,	bool,	true,	ReadWrite,	GetSet,	"Show backfaces and silhouettes? (whether or not this has an effect depends on the used scene renderer)",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		bool GetShowColorGradientBackground() const;
		void SetShowColorGradientBackground(bool bValue);
		bool GetShowBackfacesAndSilhouettes() const;
		void SetShowBackfacesAndSilhouettes(bool bValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLViewerQtConfig();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~PLViewerQtConfig();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool m_bShowColorGradientBackground;	/**< Show color gradient background? (whether or not this has an effect depends on the used scene renderer) */
		bool m_bShowBackfacesAndSilhouettes;	/**< Show backfaces and silhouettes? (whether or not this has an effect depends on the used scene renderer) */


};


#endif // __CONFIG_H__
