
// Entry point of the os
void main()
{
	*((unsigned short*)0xB8000) = 0xF044;
}
