#include "std/String.h"

#include <std/mem.h>

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
        _allocData(OTHER.data);
    }

    String::~String()
    {
        // Free
        _dallocData();
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

    String &String::operator=(const String &OTHER)
    {
        // Free
        _dallocData();

        // Copy
        _size = OTHER._size;
        _allocData(OTHER._data);

        return *this;
    }

}
