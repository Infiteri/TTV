#include "disk.h"
#include "stdio.h"

void _cdecl cstart_(unsigned short bootDrive)
{
    Disk disk;
    if (!DiskInitialize(&disk, bootDrive))
    {
        printf("Couldn't initialize disk\n");
        printf("Drive number: %hd", bootDrive);
        return;
    }
    else
        printf("Disk initialized\n");

    printf("Test %% %s %c %d %lx %llu %hd %hhd\n", "abc", 'z', 1, 2ul, 3ull, bootDrive, (char)5);
    for (;;)
        ;
}
