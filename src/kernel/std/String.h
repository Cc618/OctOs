#pragma once

// String class

#include <std/types.h>

namespace std
{
    class String
    {
    public:
        // Constructors //
        String();
        explicit String(const sz SIZE);
        String(cstr data);
        String(const String &OTHER);
        ~String();

    public:
        // Methods //
        
    public:
        // Getters //
        inline sz size() const
        { return _size; }

        inline cstr data() const
        { return _data; }

        inline str data()
        { return _data; }

    public:
        // Operators //
        // Set
        String &operator=(const String &OTHER);

        // Concatenate
        String operator+(const String &OTHER) const;

        // Cast
        operator cstr() const;

        // Access
        char operator[](const sz i) const;
        char &operator[](const sz i);

        // Compare
        bool operator==(const String &OTHER) const;
        bool operator==(cstr OTHER) const;

    private:
        // Methods //
        // Allocates the data of size _size
        // !!! Doesn't deallocate the old data
        void _allocData(cstr data);
        void _allocData();

        // Deallocates the data
        void _dallocData();

    private:
        // Attributes //
        str _data;
        sz _size;
    };
}
