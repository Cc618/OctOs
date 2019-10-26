#include "std/io.h"

#include <std/mem.h>

#include "drivers/ports.h"

namespace std
{
	void fillScreen(const byte FORMAT)
	{
		for (sz i = VIDEO_MEMORY_START; i < VIDEO_MEMORY_END; i += 2)
			*((u16*)i) = (u32)FORMAT << 8;
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

	void enableCursor()
	{
		// outb(0x0A, 0x3D4);
		// outb((inb(0x3D5) & 0xC0) | cursor_start, 0x3D5);
	
		// outb(0x0B, 0x3D4);
		// outb((inb(0x3D5) & 0xE0) | cursor_end, 0x3D5);

		outb(0x0A, 0x3D4);
		outb(0x00, 0x3D5);
	}

	void disableCursor()
	{
		outb(0x0A, 0x3D4);
		outb(0x20, 0x3D5);
	}
} // namespace std
