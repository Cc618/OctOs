#include "std/mem.h"

#include <std/err.h>
#include <std/io.h>

namespace std
{
	// Classes //
	// An allocated block in memory
	// without the data part which is after
	struct AllocationBlockHeader
	{
		// Size of the data block
		sz size;

		// Next or previous block
		// nullptr if first / last
		AllocationBlockHeader *previous;
		AllocationBlockHeader *next;
	} __attribute__((packed));

	// Constants //
	// Heap offsets
	constexpr sz HEAP_START = 0x100000;
	constexpr sz HEAP_SIZE = 0x10000;
	constexpr sz HEAP_END = HEAP_START + HEAP_SIZE;

	// Variables //
	// The last allocated block
	AllocationBlockHeader *lastBlock = nullptr;

	// Functions //
	void *alloc(const sz SIZE)
	{
	
		// TODO : Align SIZE to 32 bits

		

		// The address where we can allocate memory
		sz address;

		// This is the first block to allocate
		if (lastBlock == nullptr)
			address = HEAP_START;
		else
		{
			// Put the block after the last block
			address = (sz)lastBlock + sizeof(AllocationBlockHeader) + lastBlock->size;
		}
		
		// Test for size
		if (address + sizeof(AllocationBlockHeader) + SIZE >= HEAP_END)
		{
			// TODO : Bad alloc
			rawWrite("alloc: BAD ALLOC", 320);
		}

		// TODO : Update previous block
		// TODO : Find other block if no place
		

		// Create the block and set memory
		AllocationBlockHeader *block = (AllocationBlockHeader*)address;
		block->size = SIZE;
		block->previous = lastBlock;
		block->next = nullptr;

		// Update
		lastBlock = block;




		// rawWriteHex((i32)block, 160);



		// Return a pointer to the data, not the header
		return (void*)((byte*)block + sizeof(AllocationBlockHeader));
	}
} // namespace std
