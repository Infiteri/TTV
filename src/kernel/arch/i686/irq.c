#include "irq.h"
#include "arch/i686/io.h"
#include "arch/i686/isr.h"
#include "arch/i686/pic.h"
#include <stddef.h>
#include <stdio.h>

#define PIC_REMAP_OFFSET 0x20

IRQHandler IRQHandlers[16];

void i686_IRQHandler(Registers *reg)
{
    int irq = reg->Interrupt - PIC_REMAP_OFFSET;

    uint8_t pic_isr = i686_PICReadIRQRequestRegister();
    uint8_t pic_irr = i686_PICReadIRQRequestRegister();

    if (IRQHandlers[irq] != NULL)
    {
        IRQHandlers[irq](reg);
    }
    else
    {
        printf("Unhandled IRQ %d  ISR=%x  IRR=%x...\n", irq, pic_isr, pic_irr);
    }

    // send EOI
    i686_PICSendEndOfInterrupt(irq);
}

void i686_IRQInitialize()
{
    i686_PICConfigure(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8);

    for (int i = 0; i < 16; i++)
        i686_ISRRegisterHandler(PIC_REMAP_OFFSET + i, i686_IRQHandler);

    i686_EnableInterrupts();
}

void i686_IRQRegisterHanlder(int irq, IRQHandler handler) { IRQHandlers[irq] = handler; }
