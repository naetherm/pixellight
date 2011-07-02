/*********************************************************\
 *  File: SceneRendererPassTreeItem.h                    *
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


#ifndef __PLQT_SCENERENDERERPASSTREEITEM_H__
#define __PLQT_SCENERENDERERPASSTREEITEM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLQt/DataModels/TreeItemBase.h"
#include "SceneRendererDataModel.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLScene {
	class SceneRendererPass;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLQt {
namespace DataModels {
namespace SceneRendererDataModel {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer pass tree item
*/
class SceneRendererPassTreeItem : public TreeItemBase {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit SceneRendererPassTreeItem(PLScene::SceneRendererPass *item, QObject *parent = nullptr);
		virtual QVariant data(const int column, const int role);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLScene::SceneRendererPass *m_pPass;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SceneRendererDataModel
} // DataModels
} // PLQt


#endif // __PLQT_SCENERENDERERPASSTREEITEM_H__
