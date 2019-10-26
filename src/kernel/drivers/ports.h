#pragma once

#include <std/types.h>

// Constants
namespace port
{
	//// VGA ////
	// Selects the vga register to set
	constexpr std::u16 VGA_SELECT = 0x3D4;
	// Set the selected vga register value
	constexpr std::u16 VGA_DATA = 0x3D5;

	//// Keyboard ////
	// Keyboard IO
	constexpr std::u16 KEYBOARD = 0x60;
} // namespace port


// Output byte to port
// Defined in kernel.asm
extern "C" void outb(std::byte value, std::u16 port);

// Receive byte from port
// Defined in kernel.asm
extern "C" std::byte inb(std::u16 port);
