#include "PR/os_internal.h"
#include "PR/rcp.h"
#include "osint.h"
#include "assert.h"

s32 __osSpRawReadIo(u32 devAddr, u32* data) {
#ifdef _DEBUG
    assert((devAddr & 0x3) == 0);
    assert(data != NULL);
#endif
    if (__osSpDeviceBusy()) {
        return -1;
    }

    *data = IO_READ(devAddr);
    return 0;
}
