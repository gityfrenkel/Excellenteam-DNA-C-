#include "MemoryAllocation.h"
#include <stdio.h>
#include <malloc.h>

void test_ctor()
{
    MemoryAllocator* pointer;
    void *m = malloc(sizeof(size_t) * 7);
    if(m == NULL)
        printf("failed malloc function");
    pointer = MemoryAllocator_init(m, 220);
    if(pointer->m_size == 220 * sizeof(size_t))
        printf("ok");
}



int main()
{
    test_ctor();
    printf("Hello, World!\n");
    return 0;
}