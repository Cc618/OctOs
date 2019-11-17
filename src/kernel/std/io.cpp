#include "std/io.h"

#include <std/mem.h>

#include "drivers/ports.h"

namespace std
{
	// Constants //
	// Weight of the cursor
	constexpr byte CURSOR_STYLE = 0x0D;

	// Global variable //
	// The offset from the origin of the cursor
	u16 cursorOffset = 0;

	// The minimal position of the cursor for user input
	u16 userInputMinCursorOffset = 1;

	// Internal Functions //
	// Converts byte from 0 to 15 to hex char representation
	char _rawWriteByteGetHex(const byte VALUE)
	{
		if (VALUE < 10)
			return '0' + (char)VALUE;

		return 'A' + (char)VALUE - 0xA;
	}

	// Updates the cursor position
	// If the cursor is outside of the screen, it will be remapped
	// at the start of screen
	void _updateCursorOffset()
	{
		// End of screen
		if (cursorOffset >= VIDEO_MEMORY_CHAR_COUNT)
			scrollScreen();

		// High
		outb(0x0E, port::VGA_SELECT);
		outb((cursorOffset & 0xFF00) >> 8, port::VGA_DATA);

		// Low
		outb(0x0F, port::VGA_SELECT);
		outb(cursorOffset & 0xFF, port::VGA_DATA);
	}

	// Functions //
	void fillScreen(const byte FORMAT)
	{
		for (sz i = VIDEO_MEMORY_START; i < VIDEO_MEMORY_END; i += 2)
			*((u16*)i) = (u32)FORMAT << 8;
	}

	void scrollScreen()
	{
		// The amount of data to move
		constexpr sz CHAR_PADDING = VIDEO_MEMORY_WIDTH;
		constexpr sz BYTE_PADDING = CHAR_PADDING * 2;

		// Update cursor
		cursorOffset = userInputMinCursorOffset = VIDEO_MEMORY_CHAR_COUNT - CHAR_PADDING;

		// Scroll screen
		for (byte *i = (byte*)(VIDEO_MEMORY_START + BYTE_PADDING); i != (byte*)VIDEO_MEMORY_END; ++i)
			*(i - BYTE_PADDING) = *i;
		
		// Fill the not filled part at the end 
		for (u16 *j = (u16*)(VIDEO_MEMORY_END - BYTE_PADDING); j != (u16*)VIDEO_MEMORY_END; ++j)
			*j = EMPTY_CHAR;
	}

	void newLine()
	{
		// Align cursor
		cursorOffset += VIDEO_MEMORY_WIDTH;
		cursorOffset -= cursorOffset % VIDEO_MEMORY_WIDTH;

		// Update display
		_updateCursorOffset();
	}

	void rmChar()
	{
		// Can't go back
		if (cursorOffset <= userInputMinCursorOffset)
		{
			cursorOffset = userInputMinCursorOffset;
			return;
		}

		// Go backwards
		--cursorOffset;

		// Delete previous char
		((char*)VIDEO_MEMORY_START)[cursorOffset << 1] = 0;

		// Update display
		_updateCursorOffset();
	}

	void print(cstr s)
	{
		while (*s != '\0')
		{
			putChar(*s);
			++s;
		}
	}

	void puts(cstr s)
	{
		print(s);
		newLine();
	}

	// TODO : Other chars
	void putChar(const char c)
	{
		switch (c)
		{
		case '\n':
			// Line feed
			newLine();
			break;

		default:
			putRawChar(c);
		}
	}

	void putRawChar(const char c)
	{
		// Get the address to write in memory
		char *target = (char*)(VIDEO_MEMORY_START + (cursorOffset << 1));

		// Outside of video memory (screen)
		if (target >= (char*)VIDEO_MEMORY_END)
			return;

		// Display char
		*target = c;

		// Update cursor
		++cursorOffset;
		_updateCursorOffset();
	}

	void putRawByte(const byte VALUE)
	{
		// Write
		rawWriteByte(VALUE, cursorOffset);

		// Update cursor
		cursorOffset += 2;
		_updateCursorOffset();
	}


	void rawWrite(cstr STRING, const sz OFFSET)
	{
		for (sz i = VIDEO_MEMORY_START + (OFFSET << 1); i < VIDEO_MEMORY_END; i += 2)
		{
			// The caracter to display
			const char c = *STRING++;

			// End of string
			if (c == '\0')
				break;

			// Display char
			*((char*)i) = c;
		}
	}

	void rawWriteByte(const byte VALUE, const sz OFFSET)
	{
		// Address to write
		char *address = (char*)(VIDEO_MEMORY_START + (OFFSET << 1));

		// Outside of video memory, no exceptions
		if (address >= (char*)VIDEO_MEMORY_END)
			return;

		// 4 first bits
		const byte UPPER = (VALUE & 0xF0) >> 4;

		// Write
		*address = _rawWriteByteGetHex(UPPER);

		// Next char
		address += 2;

		// Outside of video memory, no exceptions
		if (address >= (char*)VIDEO_MEMORY_END)
			return;

		// 4 last bits
		const byte LOWER = VALUE & 0xF;

		// Write
		*address = _rawWriteByteGetHex(LOWER);
	}

	void rawWriteHex(const i32 VALUE, const sz OFFSET)
	{
		// Write each byte
		rawWriteByte((VALUE & (0xFF << 24)) >> 24, OFFSET);
		rawWriteByte((VALUE & (0xFF << 16)) >> 16, OFFSET + 2);
		rawWriteByte((VALUE & (0xFF << 8)) >> 8, OFFSET + 4);
		rawWriteByte(VALUE & 0xFF, OFFSET + 6);
	}

	void enableCursor()
	{
		// Set address (index)
		outb(0x0A, port::VGA_SELECT);

		// Set data
		outb(CURSOR_STYLE, port::VGA_DATA);
	}

	void disableCursor()
	{
		// Set address (index)
		outb(0x0A, port::VGA_SELECT);

		// Set data
		outb(0x20, port::VGA_DATA);
	}

	void setCursorPosition(const u16 x, const u16 y)
	{
		// Update cursor position
		cursorOffset = x + y * VIDEO_MEMORY_WIDTH;
		_updateCursorOffset();
	}

	void moveCursor(const u16 OFFSET)
	{
		// Update cursor position
		cursorOffset += OFFSET;
		_updateCursorOffset();
	}

	void setUserInputMinCursorPosition(const u16 x, const u16 y)
	{
		setUserInputMinCursorOffset(x + y * VIDEO_MEMORY_WIDTH);
	}

	void setUserInputMinCursorOffset(const u16 OFFSET)
	{
		// Can't be outside of screen
		if (OFFSET > VIDEO_MEMORY_CHAR_COUNT)
			userInputMinCursorOffset = 0;

		userInputMinCursorOffset = OFFSET;	
	}
} // namespace std
