#include <std/io.h>
#include <std/err.h>
#include <std/mem.h>
#include <std/globals.h>
#include <std/cmd.h>
#include <std/String.h>
#include <std/Stream.h>
#include <std/Array.h>
#include <cmd/Command.h>

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






// // TODO : mv Array.h
// namespace std
// {
// 	template <typename T>
// 	class Array
// 	{
// 	public:
// 		explicit Array(const sz SIZE = 0)
// 			: _size(SIZE)
// 		{
// 			_allocData();
// 		}

// 		// TODO : move...
// 		~Array()
// 		{
// 			dalloc(_data);
// 		}

// 	public:
// 		T &operator[](const sz i)
// 		{
// 			// TODO : Verify
// 			return _data[i];
// 		}

// 		T operator[](const sz i) const
// 		{
// 			// TODO : Verify
// 			return _data[i];
// 		}

// 	private:
// 		// Allocates the data of size _size
// 		void _allocData()
// 		{
// 			_data = (T*)alloc(sizeof(T) * _size);
// 		}

// 	private:
// 		sz _size;
// 		T *_data;
// 	};
// } // namespace std




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

	// Reset cursor
	setCursorPosition(0, 0);

	// Hello display
	puts("Welcome to OctOs 0.0.1");

	// Prepare user input
	displayShellInput();


	// TODO : Can't type without cursor
	// disableCursor();


	// Array<String> args(1);
	// args[0] = "-1";

	// execCommand("hw"); //, args);

	// TODO : Error command not found
	// TODO : Error command args
}

