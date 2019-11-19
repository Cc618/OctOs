#include "std/String.h"

#include <std/mem.h>
#include <std/err.h>

namespace std
{
    String::String()
        : _size(0)
    {
        _allocData();
    }

    String::String(const sz SIZE)
        : _size(SIZE)
    {
        _allocData();
    }

    String::String(cstr data)
        : _size(strSize(data))
    {
        _allocData(data);
    }

    String::String(const String &OTHER)
        : _size(OTHER._size)
    {
        // Copy data
        _allocData(OTHER._data);
    }

    String::~String()
    {
        // Free
        _dallocData();
    }

    String &String::operator=(const String &OTHER)
    {
        // Free
        _dallocData();

        // Copy
        _size = OTHER._size;
        _allocData(OTHER._data);

        return *this;
    }

    String String::operator+(const String &OTHER) const
    {
        String s(_size + OTHER._size);

        // Add this data (begin)
        cpy(_data, s._data, _size);

        // Add OTHER data (end)
        cpy(OTHER._data, s._data + _size, OTHER._size);

        return s;
    }

    String::operator cstr() const
    {
        return _data;
    }

    char String::operator[](const sz i) const
    {
        // Buffer overflow
        if (i >= _size)
            fatalError(error::MEM_OVERFLOW);

        return _data[i];
    }

    char &String::operator[](const sz i)
    {
        // Buffer overflow
        if (i >= _size)
            fatalError(error::MEM_OVERFLOW);

        return _data[i];
    }

    bool String::operator==(const String &OTHER) const
    {
        // Check size
        if (_size != OTHER._size)
            return false;
        
        // Check content
        for (sz i = 0; i < _size; ++i)
            if (_data[i] != OTHER._data[i])
                return false;
        
        // Same strings
        return true;
    }

    bool String::operator==(cstr OTHER) const
    {
        // Check content
        for (sz i = 0; i < _size; ++i)
            if (_data[i] != OTHER[i])
                return false;
        
        // Same strings
        return true;
    }


    void String::_allocData(cstr data)
    {
        // Allocates
        _data = (str)alloc(_size + 1);

        // Copy
        cpy(data, _data, _size);

        // Set end
        _data[_size] = '\0';
    }

    void String::_allocData()
    {
        // Allocates
        _data = (str)alloc(_size + 1);

        // Set end
        _data[_size] = '\0';
    }

    void String::_dallocData()
    {
        dalloc(_data);
        _data = nullptr;
    }
}
