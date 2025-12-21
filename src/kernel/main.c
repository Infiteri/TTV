#include "hal/hal.h"
#include "memory.h"
#include "stdint.h"
#include "stdio.h"

extern uint8_t __bss_start;
extern uint8_t __end;

void __attribute__((section(".entry"))) start(uint16_t bootDrive)
{
    memset(&__bss_start, 0, (&__end) - (&__bss_start));

    HALInitialize();

    clrscr();

    printf("Initialized %i\r\n", bootDrive);

    __asm("int $0x2");
    printf("Initialized %i\r\n", bootDrive);
    __asm("int $0x3");
    printf("Initialized %i\r\n", bootDrive);
    __asm("int $0x4");
    printf("Initialized %i\r\n", bootDrive);

    for (;;)
        ;
}
