/*********************************************************\
 *  File: HashMap.h                                      *
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


#ifndef __PLCORE_CONTAINER_HASHMAP_H__
#define __PLCORE_CONTAINER_HASHMAP_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Container/Map.h"
#include "PLCore/Container/Functions.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower> class HashMapIterator;
template <class KeyType, class ValueType, class Hasher, class Comparer, class Grower> class HashMapKeyIterator;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Hash map template
*
*  @remarks
*    The hash map is using a hashing function to calculate indices to elements. If there are
*    too many elements in the map which will produce more collisions, a grow function
*    decides when to grow the hash map and how much.
*    There are some ways to avoid collisions:
*    1. The hash map size should be a prime number: It can be mathematically proven that the
*       probability of collisions is less if we let the hash function perform % on a prime number
*       rather than on a non-prime number.
*    2. Spreading the values: For example, let the hash function be smart enough to distribute its
*       return values as evenly as possible. How to determine the best algorithm for the hash function
*       depends on the hash map usage.
*    3. Increasing the array's size: The more "free slots" in the hash map, the less probability of
*       collisions. So, to avoid collisions, use a clever grow function. But try to avoid to grow the
*       hash map frequently because that's not performant.
*
*  @note
*    - Collisions are solved by using a linked list per slot
*/
template <class KeyType, class ValueType, class Hasher = HashFunction, class Comparer = CompareFunction, class Grower = GrowFunction>
class HashMap : public Map<KeyType, ValueType> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>;
	friend class HashMapKeyIterator<KeyType, ValueType, Hasher, Comparer, Grower>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nNumOfSlots
		*    Initial number of slots (must be >= 1, should be a prime number)
		*/
		HashMap(uint32 nNumOfSlots = 199);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		HashMap(const HashMap<KeyType, ValueType, Hasher, Comparer, Grower> &cSource);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~HashMap();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    'HashMap' to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Map<KeyType, ValueType> &operator =(const HashMap<KeyType, ValueType, Hasher, Comparer, Grower> &cSource);

		/**
		*  @brief
		*    Returns the current number of slots
		*
		*  @return
		*    Current number of slots
		*/
		uint32 GetNumOfSlots() const;

		/**
		*  @brief
		*    Returns some statistics
		*
		*  @param[out] nNumOfCollisions
		*    Will receive the number of collisions
		*  @param[out] nNumOfFreeSlotsLists
		*    Will receive the number of free slots lists
		*
		*  @note
		*    - If there are a lot of collisions and also a lot of free slots lists you should
		*      try to use a more efficient hash function
		*/
		void GetStatistics(uint32 &nNumOfCollisions, uint32 &nNumOfFreeSlotsLists) const;


	//[-------------------------------------------------------]
	//[ Private structures                                    ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal hash string template
		*
		*  @remarks
		*    Slot stores a key/value pair.
		*/
		struct Slot {
			KeyType    Key;				/**< The key */
			ValueType  Value;			/**< The value */
			Slot      *pNextSlot;		/**< Pointer to the next hash slot, can be a null pointer */
			Slot      *pPreviousSlot;	/**< Pointer to the previous hash slot, can be a null pointer */
		};


	//[-------------------------------------------------------]
	//[ Private classes                                       ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Internal hash map slots template
		*
		*  @remarks
		*    The slots list stores a list of hash slot objects.
		*/
		class SlotsList {


			//[-------------------------------------------------------]
			//[ Friends                                               ]
			//[-------------------------------------------------------]
			friend class HashMap<KeyType, ValueType, Hasher, Comparer, Grower>;
			friend class HashMapIterator<KeyType, ValueType, Hasher, Comparer, Grower>;
			friend class HashMapKeyIterator<KeyType, ValueType, Hasher, Comparer, Grower>;


			//[-------------------------------------------------------]
			//[ Public functions                                      ]
			//[-------------------------------------------------------]
			public:
				/**
				*  @brief
				*    Constructor
				*/
				SlotsList();

				/**
				*  @brief
				*    Destructor
				*/
				~SlotsList();

				/**
				*  @brief
				*    Copy operator
				*
				*  @param[in] cSource
				*    'SlotsList' to copy from
				*/
				void operator =(const SlotsList &cSource);

				/**
				*  @brief
				*    Clears the hash slots
				*/
				void Clear();

				/**
				*  @brief
				*    Adds a new element to the hash map slot list
				*
				*  @param[in] Key
				*    The key of the element which should be added
				*  @param[in] Value
				*    The value which should be added
				*
				*  @see
				*    - Set()
				*/
				void Add(const KeyType &Key, const ValueType &Value);

				/**
				*  @brief
				*    Replaces the value of a map element
				*
				*  @param[in] Key
				*    The key of the element
				*  @param[in] NewValue
				*    The new value of the element
				*
				*  @return
				*    'true' if all went fine, else 'false' (key not found?)
				*
				*  @see
				*    - Set()
				*/
				bool Replace(const KeyType &Key, const ValueType &NewValue);

				/**
				*  @brief
				*    Sets (adds or replaces) the value of a map element
				*
				*  @param[in] Key
				*    The key of the element
				*  @param[in] Value
				*    The set value of the element
				*
				*  @return
				*    'false' if a new element was added, 'true' if the value was replaced
				*
				*  @remarks
				*    This function is a combination of the add and replace function and 'just' assigns
				*    a value to a given key without taking care of whether or not there's already an
				*    element with the given key inside the map.
				*
				*  @see
				*    - Add()
				*    - Replace()
				*/
				bool Set(const KeyType &Key, const ValueType &Value);

				/**
				*  @brief
				*    Removes an element from the hash map slot list
				*
				*  @param[in] Key
				*    The key which should be removed
				*
				*  @return
				*    'true' if all went fine, else 'false'
				*/
				bool Remove(const KeyType &Key);

				/**
				*  @brief
				*    Removes all elements with a certain value from the map
				*
				*  @param[in] Value
				*    Value to look for
				*
				*  @return
				*    Number of removed elements
				*/
				uint32 RemoveValue(const ValueType &Value);

				/**
				*  @brief
				*    Returns the value of a given key
				*
				*  @param[in] Key
				*    The key
				*
				*  @return
				*    Reference to the value corresponding to the key, reference to the 'Null'-object on error
				*/
				const ValueType &Get(const KeyType &Key) const;

				/**
				*  @brief
				*    Returns the value of a given key
				*
				*  @param[in] Key
				*    The key
				*
				*  @return
				*    Reference to the value corresponding to the key, reference to the 'Null'-object on error
				*/
				ValueType &Get(const KeyType &Key);


			//[-------------------------------------------------------]
			//[ Private functions                                     ]
			//[-------------------------------------------------------]
			public:
				/**
				*  @brief
				*    Copy constructor
				*
				*  @param[in] cSource
				*    Source to copy from
				*/
				SlotsList(const SlotsList &cSource);


			//[-------------------------------------------------------]
			//[ Private data                                          ]
			//[-------------------------------------------------------]
			private:
				Slot *m_pFirstSlot; /**< Pointer to the first hash slot, can be a null pointer */
				Slot *m_pLastSlot;  /**< Pointer to the last hash slot, can be a null pointer */


		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint32     m_nNumOfSlots;		/**< The current number of slots */
		SlotsList *m_plstSlots;			/**< Slots list, can be a null pointer (created when the first element is added) */
		uint32     m_nNumOfElements;	/**< Current number of elements within the map */


	//[-------------------------------------------------------]
	//[ Public virtual Iterable functions                     ]
	//[-------------------------------------------------------]
	public:
		virtual Iterator<ValueType> GetIterator(uint32 nIndex = 0) const;
		virtual ConstIterator<ValueType> GetConstIterator(uint32 nIndex = 0) const;
		virtual Iterator<ValueType> GetEndIterator() const;
		virtual ConstIterator<ValueType> GetConstEndIterator() const;


	//[-------------------------------------------------------]
	//[ Public virtual Map functions                          ]
	//[-------------------------------------------------------]
	public:
		virtual void Clear();
		virtual bool IsEmpty() const;
		virtual uint32 GetNumOfElements() const;
		virtual bool Add(const KeyType &Key, const ValueType &Value);
		virtual bool Replace(const KeyType &Key, const ValueType &NewValue);
		virtual bool Set(const KeyType &Key, const ValueType &Value);
		virtual bool Remove(const KeyType &Key);
		virtual uint32 RemoveValue(const ValueType &Value);
		virtual const ValueType &Get(const KeyType &Key) const;
		virtual ValueType &Get(const KeyType &Key);
		virtual Iterator<KeyType> GetKeyIterator(uint32 nIndex = 0) const;
		virtual ConstIterator<KeyType> GetConstKeyIterator(uint32 nIndex = 0) const;
		virtual Iterator<KeyType> GetEndKeyIterator() const;
		virtual ConstIterator<KeyType> GetConstEndKeyIterator() const;


	//[-------------------------------------------------------]
	//[ Private virtual Map functions                         ]
	//[-------------------------------------------------------]
	private:
		virtual Map<KeyType, ValueType> &operator =(const Map<KeyType, ValueType> &cMap);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Container/HashMap.inl"


#endif // __PLCORE_CONTAINER_HASHMAP_H__