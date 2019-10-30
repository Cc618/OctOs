#include "std/err.h"

#include <std/io.h>
#include <std/mem.h>

// Print error function
#define ERR_PRINT(s) std::rawWrite(s, 0)

namespace std
{
	// All messages
	cstr MSG_MEM_NULLPTR = "Nullptr";
	cstr MSG_MEM_OVERFLOW = "Memory overflow";
	cstr MSG_MEM_ALLOC = "Heap alloc";
	cstr MSG_MEM_DALLOC = "Heap dalloc";

	cstr getErrorMsg(const error ERROR)
	{
		// Find good message
		switch (ERROR)
		{
		case error::MEM_NULLPTR:
			return MSG_MEM_NULLPTR;

		case error::MEM_OVERFLOW:
			return MSG_MEM_NULLPTR;

		case error::MEM_ALLOC:
			return MSG_MEM_ALLOC;

		case error::MEM_DALLOC:
			return MSG_MEM_DALLOC;
		}

		// Not found
		return "Unknown error";
	}

	void printError(const error ERROR)
	{
		cstr msg = getErrorMsg(ERROR);

		ERR_PRINT(msg);
	}

	void fatalError(const error ERROR)
	{
		// Blue screen of death
		fillScreen((col::BLUE << 4) | (col::WHITE));

		// Display error
		rawWrite("Fatal Error, system halt :", 0);
		rawWrite(getErrorMsg(ERROR), VIDEO_MEMORY_WIDTH);
		rawWrite("Error ID (hex) :", VIDEO_MEMORY_WIDTH * 3);
		rawWriteHex((i32)ERROR, VIDEO_MEMORY_WIDTH * 4);

		// Halt
		while (true);
	}
} // namespace std
