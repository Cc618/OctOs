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

        print("Command entered !");

        // Add a new line
        newLine();

        // Print the header before user input
        displayShellInput();

        // Enable user input
        enableCursor();
    }

    void displayShellInput()
    {
        print("> ");

        // Update caret properties
        beginUserInput();
    }

}
