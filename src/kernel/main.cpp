#include <std/io.h>
#include <std/err.h>

#include "drivers/ports.h"



extern "C" void initInterrupts();



// TODO : getChar
char getChar()
{
	// TODO : replace 0x60 by def 
	char c = 0;
	while((c = inb(0x60)) != 0){
		if(c > 0)
			return c;
	}

	return 0;
}





// Entry point of the os
extern "C" void main()
{
	using namespace std;

	// TODO : Theme
	// Yellow background, black font
	fillScreen(0xE0);


	// Interrupts
	initInterrupts();


	// Reset cursor
	setCursorPosition(0, 0);

	rawWrite("Hello world!", 0);
	rawWrite("OctOs 0.0.1", 80);

	// Todo : Remove
	disableCursor();
}
