#include "std/globals.h"

#include <std/io.h>
#include <cmd/Command.h>

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
        // std //
        // io
        cout = Stream(coutPrint, coutPutChar);

        // cmd //
        // Command
        Command::initCommands();
    }
} // namespace std
