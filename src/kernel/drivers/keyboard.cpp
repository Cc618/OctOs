#include "drivers/keyboard.h"

#include <std/io.h>
#include <std/io.h>

// Internal functions //
// Whether we can display the char
bool _isDisplayable(const char c)
{
	return
		// Digit
		(c >= '0' && c <= '9') ||
		// Upper case letter
		(c >= 'A' && c <= 'Z') ||
		// Lower case letter
		(c >= 'a' && c <= 'z') ||
		// Special chars
		(c == ' ' || c == '_');
}

void dispatchKey(const std::byte KEY)
{
	// std::fillScreen(0x98);

	// if (_isDisplayable((char)KEY))
		std::putRawByte(KEY);
	

}
