#include <std/io.h>
#include <std/err.h>

#include "drivers/ports.h"



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

	// rawWrite("Hello world!", 0);
	// rawWrite("OctOs 0.0.1", 80);


	// // Set address (index)
	// outb(0x0E, 0x3D4);
	// rawWriteByte(inb(0x3D5), 0);
	// outb(0x0F, 0x3D4);
	// rawWriteByte(inb(0x3D5), 2);



	// Reset cursor
	setCursorPosition(0, 0);
	moveCursor(3);
	rawWrite("OK!", 0);
	moveCursor(3);


	// int x = 2,
	// 	y = 4;


	// while (1)
	// {
	// 	u16 offset = x + y * 80;

	// 	// High
	// 	outb(0x0E, 0x3D4);
	// 	outb((offset & 0xFF00) >> 8, 0x3D5);

	// 	// Low
	// 	outb(0x0F, 0x3D4);
	// 	outb(offset & 0xFF, 0x3D5);


	// 	y = 8;
	// 	getChar();
	// }





	// TODO : Update function
	// disableCursor();
	// enableCursor();




}
