#include "std/Stream.h"

#include <std/io.h>
#include <std/String.h>

namespace std
{
    Stream::Stream()
        : _onStreamOutput(nullptr)
    {}

    Stream::Stream(void (*onStreamOutput)(Stream&, const String &), void (*onStreamCharOutput)(Stream&, const char))
        : _onStreamOutput(onStreamOutput), _onStreamCharOutput(onStreamCharOutput)
    {}

    Stream &Stream::operator<<(const String &s)
    {
        _onStreamOutput(*this, s);

        return *this;
    }

    Stream &Stream::operator<<(const char c)
    {
        _onStreamCharOutput(*this, c);

        return *this;
    }

    Stream &Stream::operator<<(u32 n)
    {
        // Avoid infinite loop
        if (n == 0)
            return *this << '0';

        // The max power of 10 in 32 bits
        u32 maxPower = 1'000'000'000;

        // Make the max power just above n
        // (remove useless 0s)
        while (maxPower > n)
            maxPower /= 10;

        do
        {
            // The last digit of n
            const u32 DIGIT = n / maxPower;

            // Output the digit
            *this << (char)('0' + (char)DIGIT);

            // Remove the last digit
            n -= DIGIT * maxPower;

            maxPower /= 10;
        } while (maxPower != 0);

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
