#include "std/String.h"

#include <std/mem.h>
#include <std/err.h>

namespace std
{
    // TODO : Allocate empty
    String::String()
        : _size(0)
    {
        _allocData("");
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

    void String::_allocData(cstr data)
    {
        // Allocates
        _data = (str)alloc(_size);

        // Copy
        cpy(data, _data, _size);
    }

    void String::_dallocData()
    {
        dalloc(_data);
        _data = nullptr;
    }
}
