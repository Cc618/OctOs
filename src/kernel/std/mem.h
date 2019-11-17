#pragma once

// Functions to handle memory

#include <std/types.h>

namespace std
{
	// Constants //
	// Video
	constexpr sz VIDEO_MEMORY_WIDTH = 80;
	constexpr sz VIDEO_MEMORY_HEIGHT = 25;
	constexpr sz VIDEO_MEMORY_START = 0xB8000;
	constexpr sz VIDEO_MEMORY_CHAR_COUNT = VIDEO_MEMORY_WIDTH * VIDEO_MEMORY_HEIGHT;
	constexpr sz VIDEO_MEMORY_END = VIDEO_MEMORY_START + VIDEO_MEMORY_CHAR_COUNT * 2;

	// Functions //
	// Allocates a block of data
	// Returns a pointer to the data
	void *alloc(sz size);

	// Deallocates a block of data
	void dalloc(const void *data);

	// Copies a block of COUNT bytes from src to dst
	void cpy(const void *src, void *dst, const sz COUNT);

	// C Strings //
	// Returns the size of a string
	sz strSize(cstr s);

} // namespace std
