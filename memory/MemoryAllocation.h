/*
   Created by gity on 11/23/18.
*/

#ifndef MEMORYALLOCATION_MEMORYALLOCAATION_H
#define MEMORYALLOCATION_MEMORYALLOCAATION_H
#include <stdio.h>

typedef struct MemoryAllocator MemoryAllocator;

struct MemoryAllocator
{
    void *m_memoryPool;
    size_t m_size;
};

MemoryAllocator* MemoryAllocator_init(void* memoryPool, size_t size);

void* MemoryAllocator_allocate(MemoryAllocator* allocator, size_t size);

size_t MemoryAllocator_free(MemoryAllocator* allocator, void* ptr);

size_t MemoryAllocator_optimize(MemoryAllocator* allocator);

#endif /* MEMORYALLOCATION_MEMORYALLOCAATION_H */
