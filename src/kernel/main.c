#define VIDEO_MEMORY_WIDTH 80
#define VIDEO_MEMORY_HEIGHT 25
#define VIDEO_MEMORY_CHAR_COUNT (VIDEO_MEMORY_WIDTH * VIDEO_MEMORY_HEIGHT)
#define VIDEO_MEMORY_START 0xB8000
#define VIDEO_MEMORY_END (0xB8000 + VIDEO_MEMORY_CHAR_COUNT * 2)


#define ERROR_BUFFER_OVERFLOW 0x01



void kernelException(const unsigned int CODE);
void fillScreen(const unsigned char FORMAT);
void setChar(const char c, const unsigned int i);
void printRaw(const char *STRING, const unsigned int i);





// Called when there is an exception
void kernelException(const unsigned int CODE)
{
	// Blue screen of death
	fillScreen(0x9F);

	// Display error message
	*((unsigned char*)(VIDEO_MEMORY_START)) = 'E';
	*((unsigned char*)(VIDEO_MEMORY_START + 2)) = 'r';
	*((unsigned char*)(VIDEO_MEMORY_START + 4)) = 'r';
	*((unsigned char*)(VIDEO_MEMORY_START + 6)) = 'o';
	*((unsigned char*)(VIDEO_MEMORY_START + 8)) = 'r';
	*((unsigned char*)(VIDEO_MEMORY_START + 10)) = '^';
	*((unsigned char*)(VIDEO_MEMORY_START + 12)) = '^';
	*((unsigned int*)(VIDEO_MEMORY_START + VIDEO_MEMORY_WIDTH * 2 - 4)) = CODE;

	// Loop to infinity
	while (1);
}




// Fills the screen with the good format
void fillScreen(const unsigned char FORMAT)
{
	for (unsigned int i = VIDEO_MEMORY_START; i < VIDEO_MEMORY_END; i += 2)
		*((unsigned short*)i) = (unsigned short)FORMAT << 8;
}

// Set the character at the offset i
void setChar(const char c, const unsigned int i)
{
	// Check for overflows
	if (i > VIDEO_MEMORY_CHAR_COUNT)
		kernelException(ERROR_BUFFER_OVERFLOW);
	
	// Display char
	*((char*)(VIDEO_MEMORY_START + (i << 1))) = c;
}

// Prints a string at offset i from the start of the screen
// Doesn't handle complex chars (CRLF, TABs...)
void printRaw(const char *STRING, const unsigned int i)
{
	for (unsigned int offset = VIDEO_MEMORY_START + (i << 1); offset < VIDEO_MEMORY_END; offset += 2)
	{
		// The caracter to display
		const char c = *STRING++;

		// End of string
		if (c == '\0')
			break;
		
		// Display char
		*((char*)offset) = c;
	}
}


// Entry point of the os
void main()
{
	// Yellow background, black font
	fillScreen(0xE0);

	printRaw("Hello world!", 80);
	printRaw("OctOs 0.0.1", 80 * 2);
}



