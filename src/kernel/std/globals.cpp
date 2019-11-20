#include "std/globals.h"

#include <std/io.h>

namespace std
{
    // Variables //
    Stream cout;

    // Wrappers //
    void coutPrint(Stream &t __attribute__((unused)), const String &s)
    {
        print(s);
    }

    void coutPutChar(Stream &t __attribute__((unused)), const char c)
    {
        putChar(c);
    }

    // Functions //
    void initGlobals()
    {
        cout = Stream(coutPrint, coutPutChar);
    }
} // namespace std
