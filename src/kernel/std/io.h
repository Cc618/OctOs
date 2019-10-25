#pragma once

// IO related functions

#include <std/types.h>

namespace std
{
	// Fills the screen with format
	void fillScreen(const byte FORMAT);

	// TODO : Print numbers
	// TODO : Cursor

	// TODO : Keep ?
	// Writes raw string (without special chars like TABs, CRLFs...)
	// * If the string is too long, the function stops but no exceptions are raised
	void rawWrite(cstr STRING, const sz OFFSET);
} // namespace std
