/*********************************************************\
 *  File: SNMPostProcessBlackAndWhite.cpp                *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Material/Parameter.h>
#include <PLCompositing/Shaders/PostProcessing/PostProcessManager.h>
#include "PLPostProcessEffects/SNMPostProcessBlackAndWhite.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLRenderer;
using namespace PLScene;
namespace PLPostProcessEffects {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_class_metadata(SNMPostProcessBlackAndWhite, "PLPostProcessEffects", PLCompositing::SNMPostProcess, "")
	// Constructors
	pl_constructor_1_metadata(ParameterConstructor,	PLScene::SceneNode&,	"Parameter constructor",	"")
	// Attributes
	pl_attribute_metadata(LuminanceConvert,	PLGraphics::Color3,	PLGraphics::Color3(0.299f, 0.587f, 0.184f),	ReadWrite,	"Luminance convert",													"")
	pl_attribute_metadata(MiddleIntensity,	float,				0.5f,										ReadWrite,	"If intensity is below this value, pixel is black, white otherwise",	"")
		// Overloaded SNMPostProcess attributes
	pl_attribute_metadata(Filename,			PLCore::String,		"Data/PostProcesses/BlackAndWhite.pp",		ReadWrite,	"Filename of the post process to use",									"Type='PostProcess'")
pl_class_metadata_end(SNMPostProcessBlackAndWhite)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPostProcessBlackAndWhite::SNMPostProcessBlackAndWhite(SceneNode &cSceneNode) : SNMPostProcess(cSceneNode),
	LuminanceConvert(this),
	MiddleIntensity(this),
	Filename(this)
{
	// Overwrite the default setting of the filename
	m_sFilename = "Data/PostProcesses/BlackAndWhite.pp";
}

/**
*  @brief
*    Destructor
*/
SNMPostProcessBlackAndWhite::~SNMPostProcessBlackAndWhite()
{
}


//[-------------------------------------------------------]
//[ Public virtual PLCompositing::SNMPostProcess functions ]
//[-------------------------------------------------------]
void SNMPostProcessBlackAndWhite::SetParameters()
{
	// Call base implementation
	SNMPostProcess::SetParameters();

	{ // LuminanceConvert
		Parameter *pParameter = GetParameter("LuminanceConvert");
		if (pParameter)
			pParameter->SetValue3fv(LuminanceConvert.Get());
	}

	{ // MiddleIntensity
		Parameter *pParameter = GetParameter("MiddleIntensity");
		if (pParameter)
			pParameter->SetValue1f(MiddleIntensity.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPostProcessEffects
