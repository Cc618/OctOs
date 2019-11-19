#pragma once

// Streams (only output)

#include <std/types.h>
#include <std/String.h>

namespace std
{
    // Classes //
    class Stream
    {
    public:
        // !!! Avoid using default constructor
        Stream();
        Stream(void (*onStreamOutput)(const String &), void (*onStreamCharOutput)(const char));

    public:
        Stream &operator<<(const String &s);
        Stream &operator<<(const char c);
        Stream &operator<<(u32 n);
        Stream &operator<<(const i32 n);
    
    private:
        // When << String called we use this wrapper
        // to avoid virtual functions
        void (*_onStreamOutput)(const String&);
        void (*_onStreamCharOutput)(const char);
    };
}
