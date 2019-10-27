#include <std/io.h>
#include <std/err.h>

#include "drivers/ports.h"
#include "drivers/interrupts.h"

// Entry point of the os
extern "C" void main()
{
	using namespace std;

	// TODO : Theme
	// Yellow background, black font
	fillScreen(0xE0);

	// Interrupts
	initInterrupts();

	// Hello display
	rawWrite("Hello world!", 0);
	rawWrite("OctOs 0.0.1", 80);

	// Reset cursor
	setCursorPosition(0, 3);
}


