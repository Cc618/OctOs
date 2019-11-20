#pragma once

// Streams (only output)

#include <std/types.h>

namespace std
{
    class String;

    // Classes //
    class Stream
    {
    public:
        // !!! Avoid using default constructor
        Stream();
        Stream(void (*onStreamOutput)(Stream&, const String&), void (*onStreamCharOutput)(Stream&, const char));

    public:
        Stream &operator<<(const String &s);
        Stream &operator<<(const char c);
        Stream &operator<<(u32 n);
        Stream &operator<<(const i32 n);
    
    private:
        // When << String called we use this wrapper
        // to avoid virtual functions
        void (*_onStreamOutput)(Stream&, const String&);
        void (*_onStreamCharOutput)(Stream&, const char);
    };
}
