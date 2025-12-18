#include "stdio.h"

void _cdecl cstart_(unsigned short bootDrive)
{
    printf("Test %% %s %c %d %lx %llu %hd %hhd\n", "abc", 'z', 1, 2ul, 3ull, (short)4, (char)5);
    for (;;)
        ;
}
