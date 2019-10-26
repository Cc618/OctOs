#pragma once

#include <std/types.h>

typedef std::byte key_t;

// Key constants
namespace key
{
	namespace pressed
	{
		// Special //
		constexpr key_t SPACE = 0x39;
		constexpr key_t ENTER = 0x1C;
		constexpr key_t BACKSPACE = 0x0E;
		constexpr key_t TAB = 0x0F;

		// Digits //
		constexpr key_t DIGIT_0 = 0x0B;
		constexpr key_t DIGIT_1 = 0x02;
		constexpr key_t DIGIT_2 = 0x03;
		constexpr key_t DIGIT_3 = 0x04;
		constexpr key_t DIGIT_4 = 0x05;
		constexpr key_t DIGIT_5 = 0x06;
		constexpr key_t DIGIT_6 = 0x07;
		constexpr key_t DIGIT_7 = 0x08;
		constexpr key_t DIGIT_8 = 0x09;
		constexpr key_t DIGIT_9 = 0x0A;

		// Letters //
		constexpr key_t LETTER_Q = 0x10;
		constexpr key_t LETTER_W = 0x11;
		constexpr key_t LETTER_E = 0x12;
		constexpr key_t LETTER_R = 0x13;
		constexpr key_t LETTER_T = 0x14;
		constexpr key_t LETTER_Y = 0x15;
		constexpr key_t LETTER_U = 0x16;
		constexpr key_t LETTER_I = 0x17;
		constexpr key_t LETTER_O = 0x18;
		constexpr key_t LETTER_P = 0x19;

		constexpr key_t LETTER_A = 0x1E;
		constexpr key_t LETTER_S = 0x1F;
		constexpr key_t LETTER_D = 0x20;
		constexpr key_t LETTER_F = 0x21;
		constexpr key_t LETTER_G = 0x22;
		constexpr key_t LETTER_H = 0x23;
		constexpr key_t LETTER_J = 0x24;
		constexpr key_t LETTER_K = 0x25;
		constexpr key_t LETTER_L = 0x26;

		constexpr key_t LETTER_Z = 0x2C;
		constexpr key_t LETTER_X = 0x2D;
		constexpr key_t LETTER_C = 0x2E;
		constexpr key_t LETTER_V = 0x2F;
		constexpr key_t LETTER_B = 0x30;
		constexpr key_t LETTER_N = 0x31;
		constexpr key_t LETTER_M = 0x32;
	}

	namespace released
	{
		// Digits //
		constexpr key_t DIGIT_0 = 0x8B;
		constexpr key_t DIGIT_1 = 0x82;
		constexpr key_t DIGIT_2 = 0x83;
		constexpr key_t DIGIT_3 = 0x84;
		constexpr key_t DIGIT_4 = 0x85;
		constexpr key_t DIGIT_5 = 0x86;
		constexpr key_t DIGIT_6 = 0x87;
		constexpr key_t DIGIT_7 = 0x88;
		constexpr key_t DIGIT_8 = 0x89;
		constexpr key_t DIGIT_9 = 0x8A;

		// Letters //
		constexpr key_t LETTER_Q = 0x90;
		constexpr key_t LETTER_W = 0x91;
		constexpr key_t LETTER_E = 0x92;
		constexpr key_t LETTER_R = 0x93;
		constexpr key_t LETTER_T = 0x94;
		constexpr key_t LETTER_Y = 0x95;
		constexpr key_t LETTER_U = 0x96;
		constexpr key_t LETTER_I = 0x97;
		constexpr key_t LETTER_O = 0x98;
		constexpr key_t LETTER_P = 0x99;

		constexpr key_t LETTER_A = 0x9E;
		constexpr key_t LETTER_S = 0x9F;
		constexpr key_t LETTER_D = 0xA0;
		constexpr key_t LETTER_F = 0xA1;
		constexpr key_t LETTER_G = 0xA2;
		constexpr key_t LETTER_H = 0xA3;
		constexpr key_t LETTER_J = 0xA4;
		constexpr key_t LETTER_K = 0xA5;
		constexpr key_t LETTER_L = 0xA6;

		constexpr key_t LETTER_Z = 0xAC;
		constexpr key_t LETTER_X = 0xAD;
		constexpr key_t LETTER_C = 0xAE;
		constexpr key_t LETTER_V = 0xAF;
		constexpr key_t LETTER_B = 0xB0;
		constexpr key_t LETTER_N = 0xB1;
		constexpr key_t LETTER_M = 0xB2;
	}
}

// The key dispatcher
void dispatchKey(const std::byte KEY);
