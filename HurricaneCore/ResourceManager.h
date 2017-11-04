//*******************************//
//
// Name:			ResourceManager.h
// Description:		Templated class that maps a one-to-one relationship 
//					b/n the name of a resource to an index of a vector.
//
// Author:			Edwin Chen
// Created:			Oct 01, 2016
// Last updated:	Nov 03, 2017
//
//*******************************//


#ifndef _RESOURCE_MANAGER_H
#define _RESOURCE_MANAGER_H

#include "Macro.h"
#include "Debugger.h"


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

// Description
// Contains 2 data structures: a vector and a map
// Vector contains the actual pointer to the resource
// Map holds a names that specifies a resource handle (see RESOURCE HANDLE above) that corresponds to the indices of the vector mentioned above
// If name cannot be found in map, RM returns -1 (NULL)

template <class Type>
class ResourceManager {
public:
	VECTOR(Type*) resourceVector;
	MAP(STRING, ResourceHandle<Type>)* resourceMap;

	ResourceManager()
	{
		resourceMap = new MAP(STRING, ResourceHandle<Type>);
	}

	~ResourceManager()
	{
		EmptyResourceMap();
		delete resourceMap;
		resourceMap = nullptr;
	}

	inline int GetSize() const
	{
		return resourceMap->size();
	}

	inline bool IsEmpty() const 
	{
		return resourceMap->empty();
	}

	// CLEAR EVERYTHING
	void EmptyResourceMap()
	{
		MAP(STRING, ResourceHandle<Type>)::iterator iter = resourceMap->begin();

		if (resourceMap->size() > 0)
		{
			for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
			{
				ResourceHandle<Type> rm = iter->second;
				int t = rm.GetIndex();

				delete resourceVector[t];
				resourceVector[t] = NULL;
			}
		}

		resourceVector.clear();
		resourceMap->clear();
	}

	// ADD A RESOURCE
	ResourceHandle<Type> Add(const STRING& name, Type* res)
	{
		MAP(STRING, ResourceHandle<Type>)::iterator iter = resourceMap->begin();

		if (resourceMap->size() > 0)
		{
			for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
			{
				if (iter->first == name)
				{
					return iter->second;
				}
			}
		}

		int rListSize = resourceVector.size(); // should start at 0
		resourceVector.push_back(res);
		ResourceHandle<Type> handle(rListSize);
		resourceMap->insert(iter, PAIR(STRING, int)(name, handle.index));

		return handle.index;
	}

	// REMOVE (overload 1)
	// by name
	void Remove(const STRING& name)
	{
		MAP(STRING, ResourceHandle<Type>)::iterator iter = resourceMap->begin();

		for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
		{
			if (iter->first == name)
			{
				ResourceHandle<Type> rm = iter->second;
				int t = rm.GetIndex();

				delete resourceVector[t];
				resourceVector[t] = NULL;
				resourceMap->erase(name);
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

		if (idx >= 0 && idx < int(resourceVector.size()))
		{
			result = resourceVector[idx];
		}
		return result;
	}


	// GET (overload 2)
	// Return generic type pointer
	Type* GetResource(const STRING& _name) const
	{
		Type* result = nullptr;

		MAP(STRING, ResourceHandle<Type>)::iterator iter = resourceMap->begin();

		for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
		{
			if (iter->first == _name)
			{
				ResourceHandle<Type> idx = iter->second;
				result = resourceVector[idx.index];
				break;
			}

		}
		return result;
	}



	// GET (overload 3)
	// Return resource handle (index of handle)
	ResourceHandle<Type> GetHandle(const STRING &name) const
	{
		MAP(STRING, ResourceHandle<Type>)::iterator iter = resourceMap->begin();

		ResourceHandle<Type> result(-1);

		for (iter = resourceMap->begin(); iter != resourceMap->end(); iter++)
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

#endif _RESOURCE_MANAGER_H