#include <std/io.h>
#include <std/err.h>
#include <std/mem.h>
#include <std/globals.h>
#include <std/cmd.h>
#include <std/String.h>
#include <std/Stream.h>
#include <std/Array.h>

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


	Array<int> a(5);

	a[0] = 3;
	a[1] = 1;
	a[2] = 4;
	a[3] = 1;
	a[4] = 5;


	cout << "{ ";
	cout << a[0];

	// // Add comma separated numbers
	// for (sz i = 1; i < 3; ++i)
	// {
	// 	cout << ", ";
	// 	// cout << a[i];
	// }

	cout << a.getCount();

	// cout << a[1] << a[2];
	// cout << a[1];
	
	cout << " }";


	// cout << out.str();







	// TODO : String Stream << overload
	// TODO : Array << overload
}
