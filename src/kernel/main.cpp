#include <std/io.h>
#include <std/err.h>
#include <std/mem.h>

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
	void *first = alloc(0x40);
	void *second = alloc(0x40);
	void *third = alloc(0x40);

	dalloc(second);
	void *fourth = alloc(0x40);

	// sz block = (sz)first - 0x10,
	// 	size = 0x40,
	// 	headerSize = 0x10,
	// 	next = (sz)third - headerSize;
	// DBG((sz)next - ((sz)block + headerSize + size));



	// TORM
	// DBG((i32)second);
	// DBG(*(i32*)((i32)second - 16));
	// DBG((i32)third);
	// DBG(*(i32*)((i32)third - 16 + 4));
	// DBG(*(i32*)((i32)third - 16 + 8));

	DBG((i32)second);
	DBG((i32)fourth);
}


