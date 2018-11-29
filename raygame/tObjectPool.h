#pragma once

#include <vector>
using std::vector;

template <typename T>
class tObjectPool
{
public:
	tObjectPool();                       // default initializes the object pool
	tObjectPool(size_t initialCapacity);	 // initializes the pool to have a set number of objects
	~tObjectPool();                      // destroys all objects

	T* pool;						// all objects stored in the pool
	bool* free;					// indicates whether an object is available

	T * retrieve();                      // returns a pointer to an object that will be used (returns null if none available)
	void recycle(T* obj);               // accepts a pointer that can be used in the future

	size_t size;
	size_t capacity();                  // returns the total number of objects that this pool can provide
};

template <typename T>
tObjectPool<T>::tObjectPool()
{

}

template <typename T>
tObjectPool<T>::tObjectPool(size_t initialCapacity)
{
	pool = new T[initialCapacity];
	free = new bool[initialCapacity];
	for (int i = 0; i < capacity(); ++i)
	{
		free[i] = true;
	}
	size = initialCapacity;
}

template <typename T>
tObjectPool<T>::~tObjectPool()
{

}

template <typename T>
T * tObjectPool<T>::retrieve()
{
	for (int i = 0; i < capacity(); ++i)
	{
		if (free[i])
		{
			free[i] = false;
			return &pool[i];
		}
	}
}

template <typename T>
void tObjectPool<T>::recycle(T* obj)
{
	for (int i = 0; i < capacity(); ++i)
	{
		if (pool[i] == obj)
		{
			free = true;
		}
	}
}

template <typename T>
size_t tObjectPool<T>::capacity()
{
	return size;
}