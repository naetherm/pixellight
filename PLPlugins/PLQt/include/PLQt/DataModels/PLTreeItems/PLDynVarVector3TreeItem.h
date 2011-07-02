/*********************************************************\
 *  File: PLDynVarVector3TreeItem.h                      *
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


#ifndef __PLQT_PLDYNVARVECTOR3TREEITEM_H__
#define __PLQT_PLDYNVARVECTOR3TREEITEM_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLQt/DataModels//PLTreeItems/PLDynVarStringTreeItem.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLQt {
namespace DataModels {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Dynamic variable tree item: Vector3
*/
class PLDynVarVector3TreeItem : public PLDynVarStringTreeItem {


	//[-------------------------------------------------------]
	//[ Qt definitions (MOC)                                  ]
	//[-------------------------------------------------------]
	Q_OBJECT	// All files using the Q_OBJECT macro need to be compiled using the Meta-Object Compiler (MOC) of Qt, else slots won't work!
				// (VisualStudio: Header file -> Right click -> Properties -> "Custom Build Tool")


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		explicit PLDynVarVector3TreeItem(PLCore::DynVar *dynVar, QObject *parent = nullptr);
		virtual QVariant data(const int column, const int role);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		void UpdateData();
		void UpdateDataToVar();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLMath::Vector3 m_Vector3;


	//[-------------------------------------------------------]
	//[ Private classes                                       ]
	//[-------------------------------------------------------]
	private:
		class Vector3ValueBaseTreeItem: public TreeItemBase {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector3ValueBaseTreeItem(const QString &name, QObject *parent, PLDynVarVector3TreeItem *parentItem);
				virtual QVariant data(const int column, const int role);
				bool setData(const int column, const QVariant &value, const int role);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector3ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				virtual float GetVectorData(const PLMath::Vector3 &vector) = 0;
				virtual void SetVectorData(PLMath::Vector3 &vector, float newValue) = 0;


			//[-------------------------------------------------------]
			//[ Private data                                          ]
			//[-------------------------------------------------------]
			private:
				QString					 m_Name;
				PLDynVarVector3TreeItem *m_parentItem;


		};

		class Vector3XValueTreeItem : public Vector3ValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector3XValueTreeItem(QObject *parent, PLDynVarVector3TreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector3ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				float GetVectorData(const PLMath::Vector3 &vector);
				void SetVectorData(PLMath::Vector3 &vector, float newValue);


		};

		class Vector3YValueTreeItem : public Vector3ValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector3YValueTreeItem(QObject *parent, PLDynVarVector3TreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector3ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				float GetVectorData(const PLMath::Vector3 &vector);
				void SetVectorData(PLMath::Vector3 &vector, float newValue);


		};

		class Vector3ZValueTreeItem : public Vector3ValueBaseTreeItem {


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				Vector3ZValueTreeItem(QObject *parent, PLDynVarVector3TreeItem *parentItem);


			//[-------------------------------------------------------]
			//[ Protected virtual Vector3ValueBaseTreeItem functions  ]
			//[-------------------------------------------------------]
			protected:
				float GetVectorData(const PLMath::Vector3 &vector);
				void SetVectorData(PLMath::Vector3 &vector, float newValue);


		};


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // DataModels
} // PLQt


#endif // __PLQT_PLDYNVARVECTOR3TREEITEM_H__
