#include <std/types.h>
#include <std/io.h>

#include "drivers/ports.h"
#include "drivers/keyboard.h"

using namespace std;

// Loads the IDT
extern "C" void loadIDT();

// Interrupts defined in kernel/lowlevel.asm
extern "C" void irq0();
extern "C" void irq1();
extern "C" void irq2();
extern "C" void irq3();
extern "C" void irq4();
extern "C" void irq5();
extern "C" void irq6();
extern "C" void irq7();
extern "C" void irq8();
extern "C" void irq9();
extern "C" void irq10();
extern "C" void irq11();
extern "C" void irq12();
extern "C" void irq13();
extern "C" void irq14();
extern "C" void irq15();

struct IDT_entry
{
	u16 offset_lowerbits;
	u16 selector;
	u8 zero;
	u8 type_attr;
	u16 offset_higherbits;
} __attribute__((packed));

// The IDT (256 entries)
IDT_entry IDT[256];

// Global variable which stores a pointer to the IDT descriptor
u32 idtDescriptor[2];

// Inspired by https://arjunsreedharan.org/post/99370248137/kernels-201-lets-write-a-kernel-with-keyboard
inline void remapPIC()
{
	//      	Ports :
	//				PIC1	PIC2
	// 	Command 	0x20	0xA0
	// 	Data	 	0x21	0xA1

	// ICW1 : Begin initialization
	outb(0x11, 0x20);
	outb(0x11, 0xA0);

	// ICW2 : Remap offset address of IDT
	outb(0x20, 0x21);
	outb(40, 0xA1);

	// ICW3 : Setup cascading
	outb(0x04, 0x21);
	outb(0x02, 0xA1);

	// ICW4 : Environment info
	outb(0x01, 0x21);
	outb(0x01, 0xA1);

	// Mask interrupts
	outb(0x0, 0x21);
	outb(0x0, 0xA1);
}

void initInterrupts()
{
	u32 irq0Address;
	u32 irq1Address;
	u32 irq2Address;
	u32 irq3Address;
	u32 irq4Address;
	u32 irq5Address;
	u32 irq6Address;
	u32 irq7Address;
	u32 irq8Address;
	u32 irq9Address;
	u32 irq10Address;
	u32 irq11Address;
	u32 irq12Address;
	u32 irq13Address;
	u32 irq14Address;
	u32 irq15Address;
	u32 idtAddress;

	remapPIC();

	irq0Address = (u32)irq0;
	IDT[32].offset_lowerbits = irq0Address & 0xffff;
	IDT[32].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[32].zero = 0;
	IDT[32].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[32].offset_higherbits = (irq0Address & 0xffff0000) >> 16;

	irq1Address = (u32)irq1;
	IDT[33].offset_lowerbits = irq1Address & 0xffff;
	IDT[33].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[33].zero = 0;
	IDT[33].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[33].offset_higherbits = (irq1Address & 0xffff0000) >> 16;

	irq2Address = (u32)irq2;
	IDT[34].offset_lowerbits = irq2Address & 0xffff;
	IDT[34].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[34].zero = 0;
	IDT[34].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[34].offset_higherbits = (irq2Address & 0xffff0000) >> 16;

	irq3Address = (u32)irq3;
	IDT[35].offset_lowerbits = irq3Address & 0xffff;
	IDT[35].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[35].zero = 0;
	IDT[35].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[35].offset_higherbits = (irq3Address & 0xffff0000) >> 16;

	irq4Address = (u32)irq4;
	IDT[36].offset_lowerbits = irq4Address & 0xffff;
	IDT[36].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[36].zero = 0;
	IDT[36].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[36].offset_higherbits = (irq4Address & 0xffff0000) >> 16;

	irq5Address = (u32)irq5;
	IDT[37].offset_lowerbits = irq5Address & 0xffff;
	IDT[37].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[37].zero = 0;
	IDT[37].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[37].offset_higherbits = (irq5Address & 0xffff0000) >> 16;

	irq6Address = (u32)irq6;
	IDT[38].offset_lowerbits = irq6Address & 0xffff;
	IDT[38].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[38].zero = 0;
	IDT[38].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[38].offset_higherbits = (irq6Address & 0xffff0000) >> 16;

	irq7Address = (u32)irq7;
	IDT[39].offset_lowerbits = irq7Address & 0xffff;
	IDT[39].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[39].zero = 0;
	IDT[39].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[39].offset_higherbits = (irq7Address & 0xffff0000) >> 16;

	irq8Address = (u32)irq8;
	IDT[40].offset_lowerbits = irq8Address & 0xffff;
	IDT[40].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[40].zero = 0;
	IDT[40].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[40].offset_higherbits = (irq8Address & 0xffff0000) >> 16;

	irq9Address = (u32)irq9;
	IDT[41].offset_lowerbits = irq9Address & 0xffff;
	IDT[41].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[41].zero = 0;
	IDT[41].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[41].offset_higherbits = (irq9Address & 0xffff0000) >> 16;

	irq10Address = (u32)irq10;
	IDT[42].offset_lowerbits = irq10Address & 0xffff;
	IDT[42].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[42].zero = 0;
	IDT[42].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[42].offset_higherbits = (irq10Address & 0xffff0000) >> 16;

	irq11Address = (u32)irq11;
	IDT[43].offset_lowerbits = irq11Address & 0xffff;
	IDT[43].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[43].zero = 0;
	IDT[43].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[43].offset_higherbits = (irq11Address & 0xffff0000) >> 16;

	irq12Address = (u32)irq12;
	IDT[44].offset_lowerbits = irq12Address & 0xffff;
	IDT[44].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[44].zero = 0;
	IDT[44].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[44].offset_higherbits = (irq12Address & 0xffff0000) >> 16;

	irq13Address = (u32)irq13;
	IDT[45].offset_lowerbits = irq13Address & 0xffff;
	IDT[45].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[45].zero = 0;
	IDT[45].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[45].offset_higherbits = (irq13Address & 0xffff0000) >> 16;

	irq14Address = (u32)irq14;
	IDT[46].offset_lowerbits = irq14Address & 0xffff;
	IDT[46].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[46].zero = 0;
	IDT[46].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[46].offset_higherbits = (irq14Address & 0xffff0000) >> 16;

	irq15Address = (u32)irq15;
	IDT[47].offset_lowerbits = irq15Address & 0xffff;
	IDT[47].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
	IDT[47].zero = 0;
	IDT[47].type_attr = 0x8e; /* INTERRUPT_GATE */
	IDT[47].offset_higherbits = (irq15Address & 0xffff0000) >> 16;

	/* fill the IDT descriptor */
	idtAddress = (u32)IDT;
	idtDescriptor[0] = (sizeof(struct IDT_entry) * 256) + ((idtAddress & 0xffff) << 16);
	idtDescriptor[1] = idtAddress >> 16;

	// Load the IDT with the descriptor
	loadIDT();
}

// To tell to the PIC that is the end of the interrupt
inline void endOfInterrupt()
{
	outb(0x20, 0x20);
}

inline void endOfInterruptLong()
{
	outb(0xA0, 0x20);
	outb(0x20, 0x20);
}

// Handlers //
// Handlers are called when there is an interrupt
extern "C"
{
	void irq0Handler()
	{
		// Send acknowledgement
		endOfInterrupt();
	}

	// Keyboard
	void irq1Handler()
	{
		// Dispatch
		dispatchKey(inb(port::KEYBOARD));

		// Send acknowledgement
		endOfInterrupt();
	}

	void irq2Handler()
	{
		// Send acknowledgement
		endOfInterrupt();
	}

	void irq3Handler()
	{
		// Send acknowledgement
		endOfInterrupt();
	}

	void irq4Handler()
	{
		// Send acknowledgement
		endOfInterrupt();
	}

	void irq5Handler()
	{
		// Send acknowledgement
		endOfInterrupt();
	}

	void irq6Handler()
	{
		// Send acknowledgement
		endOfInterrupt();
	}

	void irq7Handler()
	{
		// Send acknowledgement
		endOfInterrupt();
	}

	void irq8Handler()
	{
		// Send acknowledgement
		endOfInterruptLong();
	}

	void irq9Handler()
	{
		// Send acknowledgement
		endOfInterruptLong();
	}

	void irq10Handler()
	{
		// Send acknowledgement
		endOfInterruptLong();
	}

	void irq11Handler()
	{
		// Send acknowledgement
		endOfInterruptLong();
	}

	void irq12Handler()
	{
		// Send acknowledgement
		endOfInterruptLong();
	}

	void irq13Handler()
	{
		// Send acknowledgement
		endOfInterruptLong();
	}

	void irq14Handler()
	{
		// Send acknowledgement
		endOfInterruptLong();
	}

	void irq15Handler()
	{
		// Send acknowledgement
		endOfInterruptLong();
	}
}
