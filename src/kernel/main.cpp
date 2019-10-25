#include <std/io.h>

// Entry point of the os
extern "C" void main()
{
	using namespace std;
	
	// Yellow background, black font
	fillScreen(0xE0);

	rawWrite("Hello world!", 0);
	rawWrite("OctOs 0.0.1", 80);
}
