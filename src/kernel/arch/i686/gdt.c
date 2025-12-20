#include "gdt.h"
#include <stdint.h>

typedef struct
{
    uint16_t LimitLow;
    uint16_t LimitHeight;
    uint8_t BaseMiddle;
    uint8_t Access;
    uint8_t BaseLimitHi;
    uint8_t BaseHigh;
} __attribute__((packed)) GDTEntry;

//
typedef struct
{
    uint16_t Limit;
    GDTEntry *Ptr;
} __attribute__((packed)) GDTDescriptor;

typedef enum
{
#define DGA(name, val) GDT_ACCESS_##name = 0x##val

    DGA(CODE_READABLE, 02),
    DGA(DATA_WRITEABLE, 02),

    DGA(CODE_CONFORMING, 04),
    DGA(DATA_DIRECTION_NORMAL, 00),
    DGA(DATA_DIRECTION_DOWN, 04),

    DGA(DATA_SEGMENT, 10),
    DGA(CODE_SEGMENT, 18),

    DGA(DESCRIPTOR_TTS, 00),

    DGA(RING0, 00),
    DGA(RING1, 20),
    DGA(RING2, 40),
    DGA(RING3, 60),

    DGA(PRESENT, 80),
} GDT_ACCESS;

typedef enum
{
#define DFA(name, val) GDT_FLAG_##name = 0x##val

    DFA(64BIT, 20),
    DFA(32BIT, 40),
    DFA(16BIT, 00),

    DFA(GRANULARITY_1B, 00),
    DFA(GRANULARITY_4K, 80),
} GDT_FLAGS;

#define GDT_LIMIT_LOW(limit) (limit & 0xFFFF)
#define GDT_BASE_LOW(base) (base & 0xFFFF)
#define GDT_BASE_MIDDLE(base) ((base >> 16) & 0xFF)
#define GDT_FLAGS_LIMIT_HI(limit, flags) (((limit >> 16) & 0xF) | (flags & 0xF0))
#define GDT_BASE_HIGH(base) ((base >> 24) & 0xFF)

#define GDT_ENTRY(base, limit, access, flags)                                                      \
    {GDT_LIMIT_LOW(limit),                                                                         \
     GDT_BASE_LOW(base),                                                                           \
     GDT_BASE_MIDDLE(base),                                                                        \
     access,                                                                                       \
     GDT_FLAGS_LIMIT_HI(limit, flags),                                                             \
     GDT_BASE_HIGH(base)}

GDTEntry GDT[] = {
    GDT_ENTRY(0, 0, 0, 0),

    GDT_ENTRY(0, 0xFFFFF,
              GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_CODE_SEGMENT |
                  GDT_ACCESS_CODE_READABLE,
              GDT_FLAG_32BIT | GDT_FLAG_GRANULARITY_4K),
    GDT_ENTRY(0, 0xFFFFF,
              GDT_ACCESS_PRESENT | GDT_ACCESS_RING0 | GDT_ACCESS_DATA_SEGMENT |
                  GDT_ACCESS_DATA_WRITEABLE,
              GDT_FLAG_32BIT | GDT_FLAG_GRANULARITY_4K),
};

GDTDescriptor GDTDesc = {sizeof(GDT) - 1, GDT};

void __attribute__((cdecl)) i686_GDTLoad(GDTDescriptor *desc, uint16_t codeSegment,
                                         uint16_t dataSegment);

void i686_GDTInitialize() { i686_GDTLoad(&GDTDesc, i686_GDT_CODE_SEGMENT, i686_GDT_DATA_SEGMENT); }
