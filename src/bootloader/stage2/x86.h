#pragma once

#include "stdint.h"

void _cdecl x86_div64_32(u64 dividend, u32 divisor, u64 *quotientOut, u32 *remainderOut);
void _cdecl x86_WriteCharTeletype(char c, u8 page);

// Disk functions

bool _cdecl x86_Disk_Reset(u8 drive);
bool _cdecl x86_Disk_Read(u8 drive, u16 cylinder, u16 head, u16 sectors, u8 count, u8 far *out);
bool _cdecl x86_Disk_GetDriveParams(u8 drive, u8 *driveOut, u16 *c, u16 *s, u16 *h);
