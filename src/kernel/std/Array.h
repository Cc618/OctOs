#pragma once

// A static array, this array can be reallocated with a different size

#include <std/types.h>
#include <std/io.h>
#include <std/mem.h>
#include <std/err.h>
#include <std/algorithm.h>

// #include <inttypes.h>
// #include <iostream>
// #include <string>
// #include <sstream>
// #include <cstring>
// #include <cassert>

// This class was initialy from my GitHub project Cc Collections : https://github.com/Cc618/Cc-Collections

namespace std
{
	template <typename T>
	class Array
	{
	public:
		// Constructors //
		// Data is null
		Array();
		
		// Copy
		Array(const Array& OTHER);
		
		// Inits the array with COUNT elements (default value)
		explicit Array(const sz COUNT);
		
		// Inits the array with COUNT elements of value VALUE
		Array(const sz COUNT, const T& VALUE);

		~Array();

	public:
		// Methods //
		// Reallocates the data with a new size
		void resize(const sz COUNT);

	public:
		// Getters //
		// Returns the number of items
		inline sz getCount() const
		{
			return _count;
		}

		// Returns the raw data
		inline const T *getData() const
		{
			return _data;
		}

		// Returns the string version of the array (like in print but without the new line)
		String toString() const;

		// Prints the data
		void print() const;

	public:
		// Operators //
		// Set
		Array &operator=(const Array& OTHER);

		// At
		T &operator[](const sz i);
		T operator[](const sz i) const;

	private:
		// Procedures //
		// Copies an array of the same size into this array
		// !!! The size of the other array is not checked
		// !!! The size of this array is not updated
		void _copy(const Array& OTHER);

	private:
		// Attributes //
		// The raw data
		T *_data;

		// Elements amount
		sz _count;
	};


	// Constructors //
	template <typename T>
	Array<T>::Array()
		: _data(nullptr), _count(0)
	{}

	template <typename T>
	Array<T>::Array(const Array& OTHER)
		: _count(OTHER._count)
	{
		_copy(OTHER);
	}

	template <typename T>
	Array<T>::Array(const sz COUNT)
		: _count(COUNT)
	{
		// Allocate
		_data = new T[COUNT];
	}

	template <typename T>
	Array<T>::Array(const sz COUNT, const T& VALUE)
		: _count(COUNT)
	{
		// Allocate
		_data = new T[COUNT];

		// Set the data
		for (sz i = 0; i < COUNT; ++i)
			_data[i] = VALUE;
	}

	template <typename T>
	Array<T>::~Array()
	{
		// Free
		delete[] _data;
	}


	// Methods //
	template <typename T>
	void Array<T>::resize(const sz COUNT)
	{
		// For empty array, don't allocate data
		if (COUNT == 0)
		{
			// Free
			delete[] _data;

			_count = 0;
			_data = nullptr;
			
			return;
		}

		// Save old data
		T *const oldData = _data;

		// Allocate new data
		_data = new T[COUNT];

		if (oldData)
		{
			// Copy data
			cpy(oldData, _data, sizeof(T) * min(_count, COUNT));

			// Free old data
			delete[] oldData;
		}

		// Update count
		_count = COUNT;
	}


	// Getters //
	template <typename T>
	String Array<T>::toString() const
	{
		// Empty array
		if (!_data)
			return "{}";

		// TODO : Implememtation
		// Use string stream for optimization
		// std::ostringstream out;
		// out << "{ " << std::to_string(_data[0]);

		// // Add comma separated numbers
		// for (sz i = 1; i < _count; ++i)
		// 	out << ", " << std::to_string(_data[i]);
		
		// out << " }";

		// return out.str();
		return "WIP";
	}

	template <typename T>
	void Array<T>::print() const
	{
		cout << toString() << '\n';
	}

	// Operators //
	template <typename T>
	Array<T> &Array<T>::operator=(const Array& OTHER)
	{
		// Free memory
		delete[] _data;

		// Copy
		_count = OTHER._count;
		_copy(OTHER);

		return *this;
	}

	template <typename T>
	T &Array<T>::operator[](const sz i)
	{
		// Error : The index is beyond limits
		if (i >= count)
			fatalError(error::MEM_OVERFLOW);

		return _data[i];
	}

	template <typename T>
	T Array<T>::operator[](const sz i) const
	{
		// Error : The index is beyond limits
		if (i >= count)
			fatalError(error::MEM_OVERFLOW);

		return _data[i];
	}

	// Procedures //
	template <typename T>
	void Array<T>::_copy(const Array& OTHER)
	{
		// Reallocate data
		_data = new T[_count];

		// Copy data
		cpy(OTHER._data, _data, sizeof(T) * _count);
	}

	// Functions //
	// TODO : Implementation
	// template <typename T>
	// std::ostream& operator<<(std::ostream& stream, const Array<T>& ARRAY)
	// {
	// 	stream << ARRAY.toString();

	// 	return stream;
	// }
}
