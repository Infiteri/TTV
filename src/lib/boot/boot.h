#pragma once

#include <stdint.h>

typedef struct
{
    uint64_t Begin, Length;
    uint32_t Type;
    uint32_t ACPI;
} __attribute__((packed)) MemoryRegion;

typedef struct
{
    uint32_t RegionCount;
    MemoryRegion *Regions;
} MemoryInfo;

typedef struct
{
    MemoryInfo Memory;
    uint8_t BootDevice;
} BootParams;
