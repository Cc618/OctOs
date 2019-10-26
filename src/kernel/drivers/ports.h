#pragma once

#include <std/types.h>

// Output byte to port
// Defined in kernel.asm
extern "C" void outb(std::byte value, std::u16 port);

// Receive byte from port
// Defined in kernel.asm
extern "C" std::byte inb(std::u16 port);
