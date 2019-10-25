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
		HEAP_ALLOC,
	};

	// Returns the message of the error
	cstr getErrorMsg(const error ERROR);
	
	// TODO : Mv to io ?
	// Prints the error to screen
	void printError(const error ERROR);
} // namespace std
