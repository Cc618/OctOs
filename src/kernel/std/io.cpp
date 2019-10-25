#include "std/io.h"

#include <std/mem.h>

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
} // namespace std
