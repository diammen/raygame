#pragma once

#include <vector>
using std::vector;

template <typename T>
class tObjectPool
{
	ObjectPool();                       // default initializes the object pool
	ObjectPool(size_t initialCapacity); // initializes the pool to have a set number of objects
	~ObjectPool();                      // destroys all objects

	T* free;                            // pointers to objects that can be reused
	T* used;                            // pointers to objects that are currently in use
	size_t freeCount;                   // number of objects that are free to use
	size_t usedCount;                   // number of objects that are in use

	T* retrieve();                      // returns a pointer to an object that will be used (returns null if none available)
	void recycle(T* obj);               // accepts a pointer that can be used in the future

	size_t capacity();                  // returns the total number of objects that this pool can provide
};

template <typename T>
tObjectPool<T>::ObjectPool() {}

template <typename T>
tObjectPool<T>::ObjectPool(size_t initialCapacity)
{
	freeCount = initialCapacity;
}

template <typename T>
tObjectPool<T>::~ObjectPool()
{
	for (int i = 0; i < capacity(); ++i)
	{
		if (retrieve() == free)
		{
			delete free;
		}
	}
}

template <typename T>
T* tObjectPool<T>::retrieve()
{
	if (freeCount == 0)
	{
		return null;
	}
	else
	{
		return free;
	}
}

template <typename T>
void tObjectPool<T>::recycle(T* obj)
{
	*retrieve() = obj;
}

template <typename T>
size_t tObjectPool<T>::capacity()
{
	return freeCount + usedCount;
}