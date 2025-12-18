#include "disk.h"
#include "stdint.h"
#include "x86.h"

bool DiskInitialize(Disk *disk, u8 driveNumber)
{
    u8 driveType;
    u16 cyl, hd, sc;

    disk->Id = driveNumber;

    if (!x86_Disk_GetDriveParams(driveNumber, &driveType, &cyl, &sc, &hd))
        return false;

    disk->Heads = hd;
    disk->Cylinders = cyl;
    disk->Sectors = sc;
    return true;
}

bool DiskReadSectors(Disk *disk, u32 lba, u32 sectors, u8 far *out) {}
