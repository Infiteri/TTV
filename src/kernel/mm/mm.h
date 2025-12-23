#pragma once

#include "lib/boot/boot.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    MemoryInfo *MemInfo;
} MmState;

typedef struct
{
    MemoryInfo *MemInfo;
} MmInitState;

bool MmInit(MmInitState *init);
MemoryInfo *MmGetMemInfo();
