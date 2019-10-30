#pragma once

// To handle errors

#include <std/types.h>

namespace std
{
	enum error
	{
		// Pointer with null usage
		MEM_NULLPTR,
		// Can't access desired memory location / forbidden address
		MEM_OVERFLOW,
		// Not enough memory to allocate data 
		MEM_ALLOC,
		// Invalid data to deallocate
		MEM_DALLOC,
	};

	// Returns the message of the error
	cstr getErrorMsg(const error ERROR);
	
	// TODO : Mv to io ?
	// Prints the error to screen
	void printError(const error ERROR);

	// Prints the error message on a blue screen and halts the system execution
	void fatalError(const error ERROR);
} // namespace std
