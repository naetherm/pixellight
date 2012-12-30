/*********************************************************\
 *  File: SNMPostProcessSepia.h                          *
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


#ifndef __PLPOSTPROCESSEFFECTS_SEPIA_H__
#define __PLPOSTPROCESSEFFECTS_SEPIA_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color3.h>
#include <PLCompositing/SceneNodeModifiers/SNMPostProcess.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sepia camera scene node post process modifier class
*
*  @remarks
*    Manipulates the color.
*/
class SNMPostProcessSepia : public PLCompositing::SNMPostProcess {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SNMPostProcessSepia, "PLPostProcessEffects", PLCompositing::SNMPostProcess, "")
		// Attributes
		pl_attribute(Desat,			float,				0.5f,									ReadWrite,	DirectValue,	"Desaturation",							"")
		pl_attribute(Toned,			float,				1.0f,									ReadWrite,	DirectValue,	"Toning",								"")
		pl_attribute(LightColor,	PLGraphics::Color3,	PLGraphics::Color3(1.0f, 0.90f, 0.5f),	ReadWrite,	DirectValue,	"Paper tone",							"")
		pl_attribute(DarkColor,		PLGraphics::Color3,	PLGraphics::Color3(0.2f, 0.05f, 0.0f),	ReadWrite,	DirectValue,	"Stain tone",							"")
			// Overloaded SNMPostProcess attributes
		pl_attribute(Filename,		PLCore::String,		"Data/PostProcesses/Sepia.pp",			ReadWrite,	ModifyAttr,		"Filename of the post process to use",	"Type='PostProcess'")
		// Constructors
		pl_constructor_1(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		SNMPostProcessSepia(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNMPostProcessSepia();


	//[-------------------------------------------------------]
	//[ Public virtual PLCompositing::SNMPostProcess functions ]
	//[-------------------------------------------------------]
	public:
		virtual void SetParameters() override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects


#endif // __PLPOSTPROCESSEFFECTS_SEPIA_H__
