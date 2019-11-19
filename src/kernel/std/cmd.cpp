#include "std/cmd.h"

#include <std/io.h>

namespace std
{
    void evalCommand()
    {
        // Disable user input
        disableCursor();

        // Separate user input to program output
        newLine();

        // Process command
        processCommand(input());

        // Add a new line
        newLine();

        // Print the header before user input
        displayShellInput();

        // Enable user input
        enableCursor();
    }

    void displayShellInput()
    {
        // Header
        print("> ");

        // Update caret properties
        beginUserInput();
    }

    void processCommand(const String &CMD)
    {
        print(String("+") + CMD + "+");
        if (CMD == "hw")
            print("Hello world !");
    }
}
