#include <std/io.h>
#include <std/err.h>
#include <std/mem.h>
#include <std/globals.h>
#include <std/cmd.h>
#include <std/String.h>
#include <std/Stream.h>
#include <std/Array.h>

#include "drivers/ports.h"
#include "drivers/interrupts.h"


// Display value
#define DBG(val) std::rawWrite(#val " :", dbgCursor); \
	dbgCursor += 80 - dbgCursor % 80; \
	std::rawWriteHex(val, dbgCursor); \
	dbgCursor += 80 - dbgCursor % 80;


static std::u32 dbgCursor = 0;

void dbgHex(std::i32 v)
{
	std::rawWriteHex(v, dbgCursor);

	dbgCursor -= dbgCursor % 80;
	dbgCursor += 80;
}






// // TODO : mv Array.h
// namespace std
// {
// 	template <typename T>
// 	class Array
// 	{
// 	public:
// 		explicit Array(const sz SIZE = 0)
// 			: _size(SIZE)
// 		{
// 			_allocData();
// 		}

// 		// TODO : move...
// 		~Array()
// 		{
// 			dalloc(_data);
// 		}
	
// 	public:
// 		T &operator[](const sz i)
// 		{
// 			// TODO : Verify
// 			return _data[i];
// 		}

// 		T operator[](const sz i) const
// 		{
// 			// TODO : Verify
// 			return _data[i];
// 		}

// 	private:
// 		// Allocates the data of size _size
// 		void _allocData()
// 		{
// 			_data = (T*)alloc(sizeof(T) * _size);
// 		}

// 	private:
// 		sz _size;
// 		T *_data;
// 	};
// } // namespace std




// Entry point of the os
extern "C" void main()
{
	using namespace std;

	// Interrupts
	initInterrupts();

	// Init global variables
	initGlobals();

	// Setup display
	fillScreen();

	// Hello display
	puts("Hello world !");
	puts("OctOs 0.0.1");

	// Prepare user input
	displayShellInput();

	// Reset cursor
	setCursorPosition(2, 2);
	setUserInputMinCursorPosition(2, 2);

	// TODO : Can't type without cursor
	// disableCursor();








	// sz n = 10;

	// TODO : RM
	// int *a = (int*)tmpAlloc(sizeof(int) * n);


	// newLine();
	// cout << (u32)(sizeof(int) * n);
	// newLine();

	// cout << (int)a << '\n';
	// cout << *(a - 4) << '\n';
	// cout << *(a - 3) << '\n';
	// cout << *(a - 2) << '\n';
	// cout << *(a - 1) << '\n';

	// for (sz i = 0; i < n; ++i)
	// 	a[i] = i + 10;

	// for (sz i = 0; i < n; ++i)
	// 	cout << a[i] << '\n';

		// cout << *(int*)(sz)(a + i * 4) << '\n';


	// a[0] = 3;
	// a[1] = 1;
	// a[2] = 4;
	// a[3] = 1;
	// a[4] = 5;


	// for (sz i = 0; i < 5; ++i)
	// {
	// 	dbg(a, i);
	// }



	Array<int> a(5);

	a[0] = 3;
	a[1] = 1;
	a[2] = 4;
	a[3] = 1;
	a[4] = 5;


	cout << a;

}
