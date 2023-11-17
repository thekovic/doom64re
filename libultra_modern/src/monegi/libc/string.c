#include "PR/ultratypes.h"
#include "string.h"

char* strchr(const char* s, int c) {
    const char ch = c;
    while (*s != ch) {
        if (*s == 0) {
            return NULL;
        }
        s++;
    }
    return (char*)s;
}

size_t strlen(const char* s) {
    const char* sc = s;
    while (*sc) {
        sc++;
    }
    return sc - s;
}

__attribute__((used))
void *memcpy(void * restrict dest, const void * restrict src, size_t count) // 80001ACC
{
    void *orig = dest;
    void *end = dest + count;
    if (((((u32) dest) | ((u32) src)) & 7) == 0)
    {
        u32 tmp1, tmp2, tmp3, tmp4;
        void *alignend = (void*)(((u32) dest) + (count & ~31));
        while (dest != alignend)
        {
            asm volatile(
            ".set noreorder                     \n\t"
            ".set nomacro                       \n\t"
            ".set gp=64                         \n\t"
            "ld      %[tmp1], 0(%[src])         \n\t"
            "ld      %[tmp2], 8(%[src])         \n\t"
            "ld      %[tmp3], 16(%[src])        \n\t"
            "ld      %[tmp4], 24(%[src])        \n\t"
            "sd      %[tmp1], 0(%[dest])        \n\t"
            "sd      %[tmp2], 8(%[dest])        \n\t"
            "sd      %[tmp3], 16(%[dest])       \n\t"
            "sd      %[tmp4], 24(%[dest])       \n\t"
            ".set gp=32                         \n\t"
            ".set macro                         \n\t"
            ".set reorder                       \n\t"
            : [tmp1] "+&r" (tmp1),  [tmp2] "+&r" (tmp2),
              [tmp3] "+&r" (tmp3),  [tmp4] "+&r" (tmp4)
            : [src] "r" (src), [dest] "r" (dest): "memory");
            dest += sizeof(u64)*4;
            src += sizeof(u64)*4;
        }
    }
    if (((((u32) dest) | ((u32) src)) & 3) == 0)
    {
        void *alignend = (void*)(((u32) end) & ~3);
        while (dest != alignend)
        {
            *(u32*)dest = *(u32*)src;
            dest += sizeof(u32);
            src += sizeof(u32);
        }
    }
    while (dest != end)
    {
        *(u8*)dest = *(u8*)src;
        dest++;
        src++;
    }

    return orig;
}
