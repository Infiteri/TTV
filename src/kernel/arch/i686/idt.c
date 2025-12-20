#include "idt.h"
#include "util/binary.h"

typedef struct
{
    uint16_t BaseLow;
    uint16_t SegmentSelector;
    uint8_t Reserved;
    uint8_t Flags;
    uint16_t BaseHigh;
} __attribute__((packed)) IDTEntry;

typedef struct
{
    uint16_t Limit;
    IDTEntry *Ptr;
} __attribute__((packed)) IDTDescriptor;

IDTEntry IDT[256];
IDTDescriptor IDTDesc = {sizeof(IDT) - 1, IDT};

void __attribute__((cdecl)) i686_IDTLoad(IDTDescriptor *desc);

void i686_IDTSetGate(int intr, void *base, uint16_t segmentDesc, uint8_t flags)
{
    IDT[intr].BaseLow = ((uint32_t)base) & 0xFFFF;
    IDT[intr].SegmentSelector = segmentDesc;
    IDT[intr].Reserved = 0;
    IDT[intr].Flags = flags;
    IDT[intr].BaseHigh = ((uint32_t)base >> 16) & 0xFFFF;
}

void i686_IDTEnable(int intr) { FLAG_SET(IDT[intr].Flags, IDT_FLAG_PRESENT); }
void i686_IDTDisable(int intr) { FLAG_UNSET(IDT[intr].Flags, IDT_FLAG_PRESENT); }

void i686_IDTInitialize() { i686_IDTLoad(&IDTDesc); }
