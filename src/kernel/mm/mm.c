#include "mm.h"

#include "debug/debug.h"

#define MM_DEBUG(fmt, ...) DebugInfo("MM: " fmt "\r\n", ##__VA_ARGS__)

static MmState state;

bool MmInit(MmInitState *init)
{
    if (!init || !init->MemInfo)
        return false;

    state.MemInfo = init->MemInfo;

    MM_DEBUG("RC: %i", state.MemInfo->RegionCount);

    return true;
}

MemoryInfo *MmGetMemInfo() { return state.MemInfo; }
