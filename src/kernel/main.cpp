#include <std/io.h>
#include <std/err.h>
#include <std/mem.h>

#include "drivers/ports.h"
#include "drivers/interrupts.h"

// Entry point of the os
extern "C" void main()
{
	using namespace std;

	fillScreen();

	// Interrupts
	initInterrupts();

	// // Hello display
	// rawWrite("Hello world!", 0);
	// rawWrite("OctOs 0.0.1", 80);
	// rawWrite("> ", 160);

	// // Reset cursor
	// setCursorPosition(2, 2);
	// setUserInputMinCursorPosition(2, 2);

	// TODO : Can't type without cursor
	disableCursor();


	// Tests //
	void *first = alloc(32);
	void *second = alloc(64);

	rawWriteHex((i32)first, 0);
	rawWriteHex((i32)second, 80);
}


