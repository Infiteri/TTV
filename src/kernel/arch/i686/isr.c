#include "isr.h"
#include "arch/i686/idt.h"
#include <stdio.h>

void i686_ISRInitializeGates();

void i686_ISRInitialize()
{
    i686_ISRInitializeGates();
    for (int i = 0; i < 256; i++)
        i686_IDTEnable(i);
}

void __attribute__((cdecl)) i686_ISRHandler(Registers *reg)
{
    printf("Interrupt %i\r\n", reg->Interrupt);
}
