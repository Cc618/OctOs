#pragma once

// String class

#include <std/types.h>
#include <std/Stream.h>

namespace std
{
    template <typename T>
    class Array;

    class String
    {
    public:
        // Constructors //
        String();
        explicit String(const sz SIZE);
        String(cstr data);
        String(cstr data, const sz SIZE);
        String(const String &OTHER);
        
        ~String();

    public:
        // Methods //
        // Counts all occurences of the char c
        sz count(const char c) const;

        // Returns the splited string by the separator SEP
        Array<String> split(const char SEP = ' ') const;

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

        // Concatenate (absolute)
        String operator+(const String &OTHER) const;

        // Concatenate (relative)
        String &operator+=(const String &OTHER);
        String &operator+=(const char c);

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

    class StringStream : public Stream
    {
		friend Stream& operator<<(Stream&, const StringStream&);

    public:
        StringStream();
        StringStream(const String &DATA);
        StringStream(const cstr DATA);

    public:
        // Retrieves the data
        inline String str() const
        {
            return _data;
        }

    private:
        static void printWrapper(Stream &t, const String &s);
        static void putCharWrapper(Stream &t, const char c);

    private:
        String _data;
    };
}
