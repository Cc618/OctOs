#pragma once

// IO related functions

#include <std/types.h>

namespace std
{
	// VGA colors
	namespace col
	{
		constexpr byte BLACK			= 0;
		constexpr byte BLUE				= 1;
		constexpr byte GREEN			= 2;
		constexpr byte CYAN				= 3;
		constexpr byte RED				= 4;
		constexpr byte PURPLE			= 5;
		constexpr byte BROWN			= 6;
		constexpr byte GRAY				= 7;
		constexpr byte DARK_GRAY		= 8;
		constexpr byte LIGHT_BLUE		= 9;
		constexpr byte LIGHT_GREEN		= 10;
		constexpr byte LIGHT_CYAN		= 11;
		constexpr byte LIGHT_RED		= 12;
		constexpr byte LIGHT_PURPLE		= 13;
		constexpr byte YELLOW			= 14;
		constexpr byte WHITE			= 15;
	} // namespace col


	//// Display ////
	// Screen //
	// Fills the screen with format
	void fillScreen(const byte FORMAT);

	// Printing //
	// TODO : Create putChar which handles special chars
	// Puts a char at cursor position and updates the cursor
	// The char is not a special char (no check)
	void putRawChar(const char c);
	void putRawByte(const byte VALUE);


	// TODO : Print numbers

	// TODO : rm after other print methods
	// Writes raw string (without special chars like TABs, CRLFs...)
	// * If the string is too long, the function stops but no exceptions are raised
	void rawWrite(cstr STRING, const sz OFFSET);
	void rawWriteByte(const byte VALUE, const sz OFFSET);
	void rawWriteHex(const i32 VALUE, const sz OFFSET);
	// void rawWriteInt(const i32 VALUE, const sz OFFSET);



	// Cursor //
	// Enabling / desabling
	void enableCursor();
	void disableCursor();

	// Moving
	void setCursorPosition(const u16 x, const u16 y);
	void moveCursor(const u16 OFFSET);
} // namespace std
