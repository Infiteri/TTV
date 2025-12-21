#include "arch/i686/irq.h"
#include "arch/i686/isr.h"
#include "hal/hal.h"
#include "memory.h"
#include "stdint.h"
#include "stdio.h"

extern uint8_t __bss_start;
extern uint8_t __end;

void timer(Registers *regs) {}

void __attribute__((section(".entry"))) start(uint16_t bootDrive)
{
    memset(&__bss_start, 0, (&__end) - (&__bss_start));

    HALInitialize();

    clrscr();

    i686_IRQRegisterHanlder(0, timer);

    printf("Initialized %i\r\n", bootDrive);

    for (;;)
        ;
}
