#include <std/io.h>
#include <std/err.h>

#include "drivers/ports.h"

// Entry point of the os
extern "C" void main()
{
	using namespace std;

	// Yellow background, black font
	fillScreen(0xE0);


	disableCursor();


	enableCursor();


	// TODO : getChar
	char ch = 0;
	while((ch = inb(0x60)) != 0){
		if(ch > 0)
			break;
	}



	rawWrite("Hello world!", 0);
	rawWrite("OctOs 0.0.1", 80);
}
