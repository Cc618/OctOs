#pragma once

// A static array, this array can be reallocated with a different size

#include <std/types.h>
#include <std/io.h>
#include <std/mem.h>
#include <std/err.h>
#include <std/algorithm.h>

// This class was initialy from my GitHub project Cc Collections : https://github.com/Cc618/Cc-Collections

namespace std
{
	template <typename T>
	class Array
	{
		// Overload <<
		template <typename C>
		friend Stream& operator<<(Stream&, const Array<C>&);

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
		inline sz size() const
		{
			return _size;
		}

		// Returns the raw data
		inline const T *data() const
		{
			return _data;
		}

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
		sz _size;
	};


	// Constructors //
	template <typename T>
	Array<T>::Array()
		: _data(nullptr), _size(0)
	{}

	template <typename T>
	Array<T>::Array(const Array& OTHER)
		: _size(OTHER._size)
	{
		_copy(OTHER);
	}

	template <typename T>
	Array<T>::Array(const sz COUNT)
		: _size(COUNT)
	{
		if (COUNT == 0)
			_data = nullptr;
		else
			// Allocate
			_data = (T*)alloc(sizeof(T) * COUNT);
	}

	template <typename T>
	Array<T>::Array(const sz COUNT, const T& VALUE)
		: _size(COUNT)
	{
		// Allocate
		_data = (T*)alloc(sizeof(T) * COUNT);

		// Set the data
		for (sz i = 0; i < COUNT; ++i)
			_data[i] = VALUE;
	}

	template <typename T>
	Array<T>::~Array()
	{
		// Free
		if (_data != nullptr)
			dalloc(_data);
	}


	// Methods //
	template <typename T>
	void Array<T>::resize(const sz COUNT)
	{
		// For empty array, don't allocate data
		if (COUNT == 0)
		{
			// Free
			dalloc(_data);

			_size = 0;
			_data = nullptr;
			
			return;
		}

		// Save old data
		T *const oldData = _data;

		// Allocate new data
		_data = (T*)alloc(sizeof(T) *COUNT);

		if (oldData)
		{
			// Copy data
			cpy(oldData, _data, sizeof(T) * min(_size, COUNT));

			// Free old data
			dalloc(oldData);
		}

		// Update count
		_size = COUNT;
	}

	// Operators //
	template <typename T>
	Array<T> &Array<T>::operator=(const Array& OTHER)
	{
		// Free memory
		dalloc(_data);

		// Copy
		_size = OTHER._size;
		_copy(OTHER);

		return *this;
	}

	template <typename T>
	T &Array<T>::operator[](const sz i)
	{
		// Error : The index is beyond limits
		if (i >= _size)
			fatalError(error::MEM_OVERFLOW);

		return _data[i];
	}

	template <typename T>
	T Array<T>::operator[](const sz i) const
	{
		// Error : The index is beyond limits
		if (i >= _size)
			fatalError(error::MEM_OVERFLOW);

		return _data[i];
	}

	// Procedures //
	template <typename T>
	void Array<T>::_copy(const Array& OTHER)
	{
		// Reallocate data
		_data = (T*)alloc(sizeof(T) * _size);

		// Copy data
		cpy(OTHER._data, _data, sizeof(T) * _size);
	}

	// Functions //
	template <typename T>
	Stream& operator<<(Stream& stream, const Array<T>& ARRAY)
	{
		// Empty array
		if (!ARRAY._data)
			return stream << "{}";

		// Use string stream for optimization
		stream << "{ ";
		stream << ARRAY._data[0];

		// Add comma separated numbers
		for (sz i = 1; i < ARRAY._size; ++i)
			stream << ", " << ARRAY._data[i];
		
		stream << " }";

		return stream;
	}
}
