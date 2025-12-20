#pragma once

#include <stdint.h>

typedef enum
{
#define IFG(name, val) IDT_FLAG_GATE_##name = 0x##val

    IFG(TASK, 5),
    IFG(16BIT_INT, 6),
    IFG(16BIT_TRAP, 7),
    IFG(32BIT_INT, E),
    IFG(32BIT_TRAP, F),

    IDT_FLAG_RING0 = (0 << 5),
    IDT_FLAG_RING1 = (1 << 5),
    IDT_FLAG_RING2 = (2 << 5),
    IDT_FLAG_RING3 = (3 << 5),

    IDT_FLAG_PRESENT = 0x80
} IDT_FLAGS;

void i686_IDTInitialize();
void i686_IDTSetGate(int intr, void *base, uint16_t segmentDesc, uint8_t flags);
void i686_IDTEnable(int intr);
void i686_IDTDisable(int intr);
