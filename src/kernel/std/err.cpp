#include "std/err.h"

#include <std/io.h>

// Print error function
#define ERR_PRINT(s) std::rawWrite(s, 0)

namespace std
{
	// All messages
	cstr MSG_MEM_NULLPTR = "Nullptr";
	cstr MSG_MEM_OVERFLOW = "Memory overflow";
	cstr MSG_MEM_ALLOC = "Heap alloc";

	cstr getErrorMsg(const error ERROR)
	{
		// Find good message
		switch (ERROR)
		{
		case error::MEM_NULLPTR:
			return MSG_MEM_NULLPTR;

		case error::MEM_OVERFLOW:
			return MSG_MEM_NULLPTR;

		case error::MEM_ALLOC:
			return MSG_MEM_ALLOC;
		}

		// Not found
		return nullptr;
	}

	void printError(const error ERROR)
	{
		cstr msg = getErrorMsg(ERROR);

		if (!msg)
			msg = "Unknown error";

		ERR_PRINT(msg);
	}
} // namespace std
