#include <std/io.h>
#include <std/err.h>
#include <std/mem.h>
#include <std/globals.h>
#include <std/cmd.h>
#include <std/String.h>
#include <std/Stream.h>

#include "drivers/ports.h"
#include "drivers/interrupts.h"


// Display value
#define DBG(val) std::rawWrite(#val " :", dbgCursor); \
	dbgCursor += 80 - dbgCursor % 80; \
	std::rawWriteHex(val, dbgCursor); \
	dbgCursor += 80 - dbgCursor % 80;


static std::u32 dbgCursor = 0;

void dbgHex(std::i32 v)
{
	std::rawWriteHex(v, dbgCursor);

	dbgCursor -= dbgCursor % 80;
	dbgCursor += 80;
}


// Entry point of the os
extern "C" void main()
{
	using namespace std;

	// Interrupts
	initInterrupts();

	// Init global variables
	initGlobals();

	// Setup display
	fillScreen();

	// Hello display
	puts("Hello world !");
	puts("OctOs 0.0.1");

	// Prepare user input
	displayShellInput();

	// Reset cursor
	setCursorPosition(2, 2);
	setUserInputMinCursorPosition(2, 2);

	// TODO : Can't type without cursor
	// disableCursor();

	// cout << "67 + (-89) = " << (67 + (-89));

	// TODO : Fatal error when empty command
}
