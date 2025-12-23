#include "memdetect.h"
#include "stdio.h"
#include "x86.h"
#include <stdint.h>

#define MAX_REGIONS 257
MemoryRegion regions[MAX_REGIONS];
int memRegCount = 0;

void MemoryDetect(MemoryInfo *info)
{
    E820MemBlock block;
    uint32_t contId = 0;

    memRegCount = 0;
    int ret = x86_E820GetNextMemoryBlock(&block, &contId);
    printf("E820: base=0x%llx length=0x%llx type=0x%x \n", block.Base, block.Length, block.Type);

    while (ret > 0 && contId != 0)
    {
        regions[memRegCount].Begin = block.Base;
        regions[memRegCount].Length = block.Length;
        regions[memRegCount].Type = block.Type;
        regions[memRegCount].ACPI = block.ACPI;
        memRegCount++;

        printf("E820: base=0x%llx length=0x%llx type=0x%x \n", block.Base, block.Length,
               block.Type);

        ret = x86_E820GetNextMemoryBlock(&block, &contId);
    };

    info->RegionCount = memRegCount;
    info->Regions = regions;
}
