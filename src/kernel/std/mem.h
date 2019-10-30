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
	void *alloc(const sz SIZE);
} // namespace std
