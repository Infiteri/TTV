#include "arch/i686/irq.h"
#include "arch/i686/isr.h"
#include "debug/debug.h"
#include "hal/hal.h"
#include "lib/boot/boot.h"
#include "memory.h"
#include "mm/mm.h"
#include "stdint.h"
#include "stdio.h"

extern uint8_t __bss_start;
extern uint8_t __end;

void timer(Registers *regs) {}

void __attribute__((section(".entry"))) start(BootParams *params)
{
    clrscr();
    memset(&__bss_start, 0, (&__end) - (&__bss_start));

    printf("Starting kernel\r\n");

    HALInitialize();

    i686_IRQRegisterHanlder(0, timer);

    // start mm
    {
        MmInitState state;
        state.MemInfo = &params->Memory;
        if (!MmInit(&state))
        {
            printf("MM: Unable to init\r\n");
            return;
        }
    }
    for (;;)
        ;
}
