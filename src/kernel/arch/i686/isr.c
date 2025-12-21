#include "isr.h"
#include "arch/i686/idt.h"
#include "arch/i686/io.h"
#include <stddef.h>
#include <stdio.h>

ISRHandler handlers[256];

static const char *const exceptions[] = {"Divide by zero error",
                                         "Debug",
                                         "Non-maskable Interrupt",
                                         "Breakpoint",
                                         "Overflow",
                                         "Bound Range Exceeded",
                                         "Invalid Opcode",
                                         "Device Not Available",
                                         "Double Fault",
                                         "Coprocessor Segment Overrun",
                                         "Invalid TSS",
                                         "Segment Not Present",
                                         "Stack-Segment Fault",
                                         "General Protection Fault",
                                         "Page Fault",
                                         "",
                                         "x87 Floating-Point Exception",
                                         "Alignment Check",
                                         "Machine Check",
                                         "SIMD Floating-Point Exception",
                                         "Virtualization Exception",
                                         "Control Protection Exception ",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "",
                                         "Hypervisor Injection Exception",
                                         "VMM Communication Exception",
                                         "Security Exception",
                                         ""};

void i686_ISRInitializeGates();

void i686_ISRInitialize()
{
    i686_ISRInitializeGates();
    for (int i = 0; i < 256; i++)
        i686_IDTEnable(i);
}

void __attribute__((cdecl)) i686_ISRHandler(Registers *reg)
{
    if (handlers[reg->Interrupt] != NULL)
    {
        handlers[reg->Interrupt](reg);
    }
    else if (reg->Interrupt >= 32)
        printf("Unhandled interrupt %i\n", reg->Interrupt);
    else
    {
        printf("Unhandled exception %d %s\n", reg->Interrupt, exceptions[reg->Interrupt]);

        printf("  eax=%x  ebx=%x  ecx=%x  edx=%x  esi=%x  edi=%x\n", reg->eax, reg->ebx, reg->ecx,
               reg->edx, reg->esi, reg->edi);

        printf("  esp=%x  ebp=%x  eip=%x  eflags=%x  cs=%x  ds=%x  ss=%x\n", reg->esp, reg->ebp,
               reg->eip, reg->eflags, reg->cs, reg->ds, reg->ss);

        printf("  interrupt=%x  errorcode=%x\n", reg->Interrupt, reg->Error);

        printf("KERNEL PANIC!\n");
        i686_panic();
    }
}

void i686_ISRRegisterHandler(int intr, ISRHandler handler) { handlers[intr] = handler; }
