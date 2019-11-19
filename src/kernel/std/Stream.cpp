#include "std/Stream.h"

#include <std/io.h>

namespace std
{
    Stream::Stream()
        : _onStreamOutput(nullptr)
    {}

    Stream::Stream(void (*onStreamOutput)(const String &), void (*onStreamCharOutput)(const char))
        : _onStreamOutput(onStreamOutput), _onStreamCharOutput(onStreamCharOutput)
    {}

    Stream &Stream::operator<<(const String &s)
    {
        _onStreamOutput(s);

        return *this;
    }

    Stream &Stream::operator<<(const char c)
    {
        _onStreamCharOutput(c);

        return *this;
    }

    Stream &Stream::operator<<(u32 n)
    {
        // The 10 power just before 2 ^ 32
        u32 m = 1'000'000'000;

        // Skip padding
        while (m >= n)
            m /= 10;

        do
        {
            // Print as char
            *this << (char)('0' + (n - n % m) / m);

            // Remove the digit
            n %= m;

            // Update m
            m /= 10;
        }
        while (m != 0);

        return *this;
    }

    Stream &Stream::operator<<(const i32 i)
    {
        if (i >= 0)
            return *this << static_cast<u32>(i);
        else
            return *this << '-' << static_cast<u32>(-i);
    }
}
