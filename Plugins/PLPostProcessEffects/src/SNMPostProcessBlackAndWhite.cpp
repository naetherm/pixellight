/*********************************************************\
 *  File: SNMPostProcessBlackAndWhite.cpp                *
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
pl_implement_class(SNMPostProcessBlackAndWhite)


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
