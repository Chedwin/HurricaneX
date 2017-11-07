//*******************************//
//
// Name:			ResourceManager.h
// Description:		Templated class that maps a one-to-one relationship 
//					b/n the name of a __resource to an index of a vector.
//
// Author:			Edwin Chen
// Created:			Oct 01, 2016
// Last updated:	Nov 06, 2017
//
//*******************************//


#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "Macro.h"
#include "Debugger.h"
#include "HUtility.h"

namespace HurricaneEngine
{

#pragma region class RESOURCE HANDLE
	// This is merely an index number that can be check if NULL (x == -1) or not (x > -1)
	template <class Type>
	class ResourceHandle {
	public:
		int index; // leave this index PUBLIC

	public:
		ResourceHandle() : index(-1) {}
		ResourceHandle(int ind) : index(ind) {}

		inline bool IsNull() {
			return index == -1;
		}

		inline void Nullify() {
			index = -1;
		}

		inline int GetIndex() const {
			return index;
		}
	};

#pragma endregion

	///////////////////////////////////////////////////////////////////////////////////////////////

#pragma region class RESOURCE MANAGER 

// Description:
//		Contains 2 data structures: a vector and a map
//		Vector contains the actual pointer to the resource
//		Map holds a names that specifies a resource handle (see RESOURCE HANDLE above) that corresponds to the indices of the vector mentioned above
//		If name cannot be found in map, RM returns -1 (NULL)

	template <class Type>
	class ResourceManager {
	protected:
		VECTOR(Type*) _resourceVector;
		MAP(STRING, ResourceHandle<Type>)* _resourceMap;

	public:
		ResourceManager()
		{
			_resourceMap = new MAP(STRING, ResourceHandle<Type>);
		}

		~ResourceManager()
		{
			EmptyResourceMap();
			SAFE_DELETE(_resourceMap);
		}

		inline int GetSize() const
		{
			return _resourceMap->size();
		}

		inline bool IsEmpty() const
		{
			return _resourceMap->empty();
		}

		// CLEAR EVERYTHING
		void EmptyResourceMap()
		{
			MAP(STRING, ResourceHandle<Type>)::iterator iter = _resourceMap->begin();

			if (_resourceMap->size() > 0)
			{
				for (iter = _resourceMap->begin(); iter != _resourceMap->end(); iter++)
				{
					ResourceHandle<Type> rm = iter->second;
					int t = rm.GetIndex();

					delete _resourceVector[t];
					_resourceVector[t] = NULL;
				}
			}

			_resourceVector.clear();
			_resourceMap->clear();
		}

		// ADD A RESOURCE
		ResourceHandle<Type> Add(const STRING& name, Type* res)
		{
			MAP(STRING, ResourceHandle<Type>)::iterator iter = _resourceMap->begin();

			if (_resourceMap->size() > 0)
			{
				for (iter = _resourceMap->begin(); iter != _resourceMap->end(); iter++)
				{
					if (iter->first == name)
					{
						return iter->second;
					}
				}
			}

			int rListSize = _resourceVector.size(); // should start at 0
			_resourceVector.push_back(res);
			ResourceHandle<Type> handle(rListSize);
			_resourceMap->insert(iter, PAIR(STRING, int)(name, handle.index));

			return handle.index;
		}

		// REMOVE
		// by name
		void Remove(const STRING& name)
		{
			MAP(STRING, ResourceHandle<Type>)::iterator iter = _resourceMap->begin();

			for (iter = _resourceMap->begin(); iter != _resourceMap->end(); iter++)
			{
				if (iter->first == name)
				{
					ResourceHandle<Type> rm = iter->second;
					int t = rm.GetIndex();

					SAFE_DELETE(_resourceVector[t]);
					_resourceMap->erase(name);
					return;
				}
			}
		}


		// GET (overload 1)
		// Return generic type pointer
		Type* GetResource(ResourceHandle<Type> &handle) const
		{
			int idx = handle.GetIndex();
			Type *result = NULL;

			if (HUtility::InRange<int>(idx, 0, GetSize()))
				result = _resourceVector[idx];

			return result;
		}


		// GET (overload 2)
		// Return generic type pointer
		Type* GetResource(const STRING& _name) const
		{
			Type* result = nullptr;

			MAP(STRING, ResourceHandle<Type>)::iterator iter = _resourceMap->begin();

			for (iter = _resourceMap->begin(); iter != _resourceMap->end(); iter++)
			{
				if (iter->first == _name)
				{
					ResourceHandle<Type> idx = iter->second;
					result = _resourceVector[idx.index];
					break;
				}

			}
			return result;
		}

		// GET (overload 3)
		// Return generic type pointer
		Type* GetResource(unsigned int _index) const
		{
			ResourceHandle<Type> t(_index);
			return GetResource(t);
		}



		// GET (overload 4)
		// Return __resource handle (index of handle)
		ResourceHandle<Type> GetHandle(const STRING &name) const
		{
			MAP(STRING, ResourceHandle<Type>)::iterator iter = _resourceMap->begin();

			ResourceHandle<Type> result(-1);

			for (iter = _resourceMap->begin(); iter != _resourceMap->end(); iter++)
			{
				if (iter->first == name)
				{
					result = iter->second;
					return iter->second;
				}

			}
			return result;
		}

	}; // end template class ResourceManager

#pragma endregion

} // end namespace HurricaneEngine

#endif _RESOURCE_MANAGER_H