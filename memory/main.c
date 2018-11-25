#include "MemoryAllocation.h"
#include <stdio.h>
#include <malloc.h>

void test_ctor()
{
    MemoryAllocator* pointer;
    void *m = malloc(sizeof(size_t) * 7);
    if(m == NULL)
    {
        printf("failed malloc function");
        return;
    }
    pointer = MemoryAllocator_init(m, 220);
    if(pointer->m_size > 220)
        printf("init success\n");
    free(m);
}

void test_allocator()
{
    MemoryAllocator* memory_pointer;
    void* mem;
    void* m = malloc(sizeof(size_t) * 100);
    if(m == NULL)
    {
        printf("failed malloc function\n");
        return;
    }
    memory_pointer = MemoryAllocator_init(m, 220);
    mem = MemoryAllocator_allocate(memory_pointer, 16);
    mem = (void*)((size_t)mem - sizeof(size_t));
    if(*(size_t*)mem == 16)
        printf("allocated success\n");
    free(m);
}

void test_free()
{
    size_t free_memory;
    MemoryAllocator* memory_pointer;
    void* mem;
    void* m = malloc(sizeof(size_t) * 100);
    if(m == NULL)
    {
        printf("failed malloc function\n");
        return;
    }
    memory_pointer = MemoryAllocator_init(m, 220);
    mem = MemoryAllocator_allocate(memory_pointer, 12);
    mem = (void*)((size_t)mem - sizeof(size_t));
    if(*(size_t*)mem == 16)
        printf("allocated to free success\n");
    free_memory = MemoryAllocator_free(memory_pointer, (void*)((size_t)mem - sizeof(size_t)));
    if(free_memory == 0)
        printf("free memory success\n");
    free(m);
}

void test_merge_memory()
{
    size_t free_memory;
    MemoryAllocator* memory_pointer;
    void* m = malloc(sizeof(size_t) * 100);
    if(m == NULL)
    {
        printf("failed malloc function\n");
        return;
    }
    memory_pointer = MemoryAllocator_init(m, 220);
    free_memory = MemoryAllocator_optimize(memory_pointer);
    if(free_memory == 224)
        printf("optimize success\n");
    free(m);
}

int main()
{
    test_ctor();
    test_allocator();
    test_free();
    test_merge_memory();
    return 0;
}