#pragma once

#include "stdint.h"

typedef struct
{
    u8 Id;
    u16 Cylinders;
    u16 Sectors;
    u16 Heads;
} Disk;

bool DiskInitialize(Disk *disk, u8 driveNumber);
bool DiskReadSectors(Disk *disk, u32 lba, u32 sectors, u8 far *out);
