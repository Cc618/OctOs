#include "std/globals.h"

#include <std/io.h>

namespace std
{
    // Variables //
    Stream cout;

    // Wrappers //
    void coutPrint(const String &s)
    {
        print(s);
    }

    void coutPutChar(const char c)
    {
        putChar(c);
    }


    // Functions //
    void initGlobals()
    {
        cout = Stream(coutPrint, coutPutChar);
    }
} // namespace std
