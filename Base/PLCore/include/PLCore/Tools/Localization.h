/*********************************************************\
 *  File: Localization.h                                 *
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


#ifndef __PLCORE_LOCALIZATION_H__
#define __PLCORE_LOCALIZATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"
#include "PLCore/Core/Singleton.h"
#include "PLCore/Container/Array.h"
#include "PLCore/Container/HashMap.h"


//[-------------------------------------------------------]
//[ Makro definitions                                     ]
//[-------------------------------------------------------]
#define PLT(Text) PLCore::Localization::GetInstance()->Get(Text)
#define PL_TEXT(Text, Group) PLCore::Localization::GetInstance()->Get(Text, Group)


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Localization;
	class LocalizationGroup;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Localization manager
*
*  @remarks
*    The localization manager is used to 'translate' a given text into the current active
*    language. This is done by using the given text to translate as 'key' within a certain
*    group and each project can have it's own localization group to avoid conflicts. If the given
*    text to translate was found within the given localization group, the translation result is returned,
*    else the given text is returned instead. As result, within your code you ALWAYS have to use a native
*    language (within PixelLight, this is english) which is used if a text is not translated.
*    The default localization group is called 'PixelLight' and should ONLY be used for engine texts!
*
*  @verbatim
*    Usage example:
*    String sString = PLT("Translate this text");
*    String sMyString = PL_TEXT("Translate this text", "MyProject");
*  @endverbatim
*/
class Localization : public Singleton<Localization> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Singleton<Localization>;


	//[-------------------------------------------------------]
	//[ Public static data                                    ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API static const String PixelLight;	/**< "PixelLight" (default) */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the current language
		*
		*  @return
		*    The current language
		*/
		PLCORE_API String GetLanguage() const;

		/**
		*  @brief
		*    Sets the current language
		*
		*  @param[in] sLanguage
		*    The new current language
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - You can use the System::GetLocaleLanguage() function to get the current program locale language
		*    - It's recommended to call this function ONLY on startup because it's possible that some
		*      texts can't be updated on runtime if another language is set
		*/
		PLCORE_API void SetLanguage(const String &sLanguage);

		/**
		*  @brief
		*    Returns the translation of the given text
		*
		*  @param[in] sText
		*    Text to translate
		*  @param[in] sGroup
		*    Group the text to translate is in
		*
		*  @return
		*    The translation of the given text, if no translation is available for this text the
		*    given text is returned instead by default
		*/
		PLCORE_API String Get(const String &sText, const String &sGroup = PixelLight) const;

		/**
		*  @brief
		*    Returns the number of groups
		*
		*  @return
		*    The number of groups
		*/
		PLCORE_API uint32 GetNumOfGroups() const;

		/**
		*  @brief
		*    Returns a group by index
		*
		*  @param[in] nIndex
		*    Index of the group
		*
		*  @return
		*    The requested group, a null pointer on error
		*/
		PLCORE_API LocalizationGroup *GetGroup(uint32 nIndex) const;

		/**
		*  @brief
		*    Returns a group by name
		*
		*  @param[in] sName
		*    Name of the group
		*
		*  @return
		*    The requested group, a null pointer on error
		*/
		PLCORE_API LocalizationGroup *GetGroup(const String &sName) const;

		/**
		*  @brief
		*    Adds a new group
		*
		*  @param[in] sName
		*    Name of the new group
		*
		*  @return
		*    The new group, a null pointer on error (maybe there's already a group with the given name?)
		*/
		PLCORE_API LocalizationGroup *AddGroup(const String &sName);

		/**
		*  @brief
		*    Removes a group by index
		*
		*  @param[in] nIndex
		*    Index of the group
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe there's no group with the given name?)
		*/
		PLCORE_API bool RemoveGroup(uint32 nIndex);

		/**
		*  @brief
		*    Removes a group by name
		*
		*  @param[in] sName
		*    Name of the group
		*
		*  @return
		*    'true' if all went fine, else 'false' (maybe there's no group with the given name?)
		*/
		PLCORE_API bool RemoveGroup(const String &sName);

		/**
		*  @brief
		*    Removes all groups
		*/
		PLCORE_API void RemoveAllGroups();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		Localization();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Localization(const Localization &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Localization();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Localization &operator =(const Localization &cSource);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String								m_sLanguage;	/**< Current set language */
		Array<LocalizationGroup*>			m_lstGroups;	/**< Localization groups list */
		HashMap<String, LocalizationGroup*>	m_mapGroups;	/**< Localization groups map */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
PLCORE_TEMPLATE template class PLCORE_API PLCore::Singleton<PLCore::Localization>;


#endif // __PLCORE_LOCALIZATION_H__
