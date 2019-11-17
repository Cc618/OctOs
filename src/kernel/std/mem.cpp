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

		// Only to make this struct 16 bits aligned
		sz padding;
	} __attribute__((packed));

	// Constants //
	// Heap
	constexpr sz HEAP_START = 0x100000;
	constexpr sz HEAP_SIZE = 0x100;
	constexpr sz HEAP_END = HEAP_START + HEAP_SIZE;

	// Variables //
	// The last allocated block
	AllocationBlockHeader *lastBlock = nullptr;

	// Functions //
	void *alloc(sz size)
	{
		// Align size to 32 bits
		if (size % 32 != 0)
			size += 32 - size % 32;

		// The address where we can allocate memory
		AllocationBlockHeader *block = (AllocationBlockHeader*)HEAP_START;

		// This is not the first block to allocate
		if (lastBlock != nullptr)
		{
			// Put the block after the last block
			sz ADDRESS = (sz)lastBlock + sizeof(AllocationBlockHeader) + lastBlock->size;

			// The size of the entire block (header + data) needed
			const sz ALLOC_SIZE = sizeof(AllocationBlockHeader) + size;

			// Not enough space to allocate the data
			if (ADDRESS + ALLOC_SIZE >= HEAP_END)
			{
				// Find other block from the first block
				block = (AllocationBlockHeader*)HEAP_START;

				// Find new address
				while (true)
				{
					const sz FREE_SPACE = (sz)block->next - ((sz)block + sizeof(AllocationBlockHeader) + block->size);

					// The empty space where we can allocate the block header and the data
					// is big enough to allocate the data
					if (FREE_SPACE >= ALLOC_SIZE)
					{
						// The block before the new block
						AllocationBlockHeader *previous = block;

						// Set the block address
						block = (AllocationBlockHeader*)((sz)previous->next - FREE_SPACE);

						// Link it with other blocks
						previous->next->previous = block;
						block->next = previous->next;
						previous->next = block;

						break;
					}

					// Change block
					block = block->next;

					// We have looped through all blocks, there is not enough space
					if (block->next == nullptr)
						fatalError(error::MEM_ALLOC);
				}
			}
			else
				block = (AllocationBlockHeader*)ADDRESS;
		}
		else
			block->next = nullptr;

		// Set memory
		block->size = size;
		block->previous = lastBlock;

		// Update lastBlock
		lastBlock->next = block;
		lastBlock = block;

		// Return a pointer to the data, not the header
		return (void*)((sz)block + sizeof(AllocationBlockHeader));
	}

	void dalloc(const void *data)
	{

		// Retrieve the block
		AllocationBlockHeader *block = (AllocationBlockHeader*)((sz)data - sizeof(AllocationBlockHeader));

		// Test validity
		if (block->size == 0)
			fatalError(error::MEM_DALLOC);

		// Link previous and next block
		AllocationBlockHeader *previous = block->previous;
		AllocationBlockHeader *next = block->next;

		// It's the last block
		if (next == nullptr)
		{
			if (previous == nullptr)
				lastBlock = (AllocationBlockHeader*)HEAP_START;
			else
				lastBlock = previous;
		}
		else
			next->previous = previous;

		if (previous != nullptr)
			previous->next = next;

		// TODO : Useless ?
		// Set to free block of data
		block->size = 0;
	}

	void cpy(const void *src, void *dst, const sz COUNT)
	{
		const byte *s = (const byte*)src;
		byte *d = (byte*)dst;

		for (sz i = 0; i < COUNT; ++i)
		{
			// Set
			*d = *s;

			// Next
			++s;
			++d;
		}
	}

	sz strSize(cstr s)
	{
		// Save string
		const cstr OLD_S = s;

		// Find the end of the string
		while (*s != '\0')
			++s;

		// Both are byte pointers so the distance unit is 1
		return s - OLD_S;
	}
} // namespace std
