#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

#define ERROR(msg, ...)                                                                            \
    {                                                                                              \
        fprintf(stderr, msg, ##__VA_ARGS__);                                                       \
        fprintf(stderr, "\n");                                                                     \
    }

typedef unsigned char u8;
typedef u8 b8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct
{
    u8 BootJumpInstruction[3];
    u8 OemIdentifier[8];
    u16 BytesPerSector;
    u8 SectorsPerCluster;
    u16 ReservedSectors;
    u8 FatCount;
    u16 DirEntryCount;
    u16 TotalSectors;
    u8 MediaDescriptorType;
    u16 SectorsPerFat;
    u16 SectorsPerTrack;
    u16 Heads;
    u32 HiddenSectors;
    u32 LargeSectorCount;

    u8 DriveNumber;
    u8 Reserved;
    u8 Signature;
    u32 VolumeId;
    u8 VolumeLabel[11];
    u8 SystemId[8];
} __attribute__((packed)) BootSector;

typedef struct
{
    u8 Name[11];
    u8 Attributes;
    u8 _Reserved;
    u8 CreatedTimeTenths;
    u16 CreatedTime;
    u16 CreatedDate;
    u16 AccessedDate;
    u16 FirstClusterHigh;
    u16 ModifiedTime;
    u16 ModifiedDate;
    u16 FirstClusterLow;
    u32 Size;
} __attribute__((packed)) DirectoryEntry;

static BootSector bootSector;
static u8 *fat;
static DirectoryEntry *rootDirectory = NULL;
static u32 rootDirectoryEnd;

b8 ReadBootSector(FILE *disk) { return fread(&bootSector, sizeof(BootSector), 1, disk); }

b8 ReadSectors(FILE *disk, u32 lba, u32 count, void *out)
{
    b8 ok = true;
    ok = ok && (fseek(disk, lba * bootSector.BytesPerSector, SEEK_SET) == 0);
    ok = ok && (fread(out, bootSector.BytesPerSector, count, disk) == count);
    return ok;
}

b8 ReadFAT(FILE *disk)
{
    fat = (u8 *)malloc(bootSector.SectorsPerFat * bootSector.BytesPerSector);
    return ReadSectors(disk, bootSector.ReservedSectors, bootSector.SectorsPerFat, fat);
}

b8 ReadRootDirectoiry(FILE *disk)
{
    u32 lba = bootSector.ReservedSectors + bootSector.SectorsPerFat * bootSector.FatCount;
    u32 size = sizeof(DirectoryEntry) * bootSector.DirEntryCount;
    u32 sectors = (size / bootSector.BytesPerSector);
    if (size % bootSector.BytesPerSector > 0)
        sectors++;

    rootDirectoryEnd = lba + sectors;
    rootDirectory = (DirectoryEntry *)malloc(sectors * bootSector.BytesPerSector);
    return ReadSectors(disk, lba, sectors, rootDirectory);
}

DirectoryEntry *FindFile(const char *name)
{
    for (u32 i = 0; i < bootSector.DirEntryCount; i++)
    {
        if (memcmp(name, rootDirectory[i].Name, 11) == 0)
            return &rootDirectory[i];
    }

    return NULL;
}

b8 ReadFile(DirectoryEntry *entry, FILE *disk, u8 *output)
{
    b8 ok = true;
    u16 currentCluster = entry->FirstClusterLow;

    do
    {
        u32 lba = rootDirectoryEnd + (currentCluster - 2) * bootSector.SectorsPerCluster;
        ok = ok && ReadSectors(disk, lba, bootSector.SectorsPerCluster, output);
        output += bootSector.SectorsPerCluster * bootSector.BytesPerSector;

        u32 fatIndex = currentCluster * 3 / 2;
        if (currentCluster % 2 == 0)
            currentCluster = (*(u16 *)(fat + fatIndex)) & 0x0FFF;
        else
            currentCluster = (*(u16 *)(fat + fatIndex)) >> 4;

    } while (ok && currentCluster < 0x0FF8);

    return ok;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("FAT: Cannot run, expected >= 3 arguments\n");
        return -1;
    }

    FILE *disk = fopen(argv[1], "rb");
    if (!disk)
    {
        ERROR("Couldn't open disk image '%s'", argv[1]);
        return -2;
    }

    if (!ReadBootSector(disk))
    {
        ERROR("Couldn't read boot sector");
        return -3;
    }

    if (!ReadFAT(disk))
    {
        ERROR("Couldn't read FAT");
        return -4;
    }

    if (!ReadRootDirectoiry(disk))
    {
        ERROR("Couldn't read root directory");
        return -5;
    }

    DirectoryEntry *dir = FindFile(argv[2]);
    if (!dir)
    {
        ERROR("Couldn't find file '%s'", argv[2])
        return -6;
    }

    u8 *buffer = (u8 *)malloc(dir->Size + bootSector.BytesPerSector);
    if (!ReadFile(dir, disk, buffer))
    {
        ERROR("Could not read file %s\n", argv[2]);
        return -7;
    }

    for (size_t i = 0; i < dir->Size; i++)
    {
        if (isprint(buffer[i]))
            fputc(buffer[i], stdout);
        else
            printf("<%02x>", buffer[i]);
    }
    printf("\n");

    return 0;
}
