/*
   Created by gity on 11/23/18.
*/
#include "MemoryAllocation.h"
#include <malloc.h>
#include <stdbool.h>


void* next_block(void* currentAddress)
{
    return (void*)((size_t)currentAddress + sizeof(size_t) + *(size_t *)currentAddress);
}

MemoryAllocator* MemoryAllocator_init(void* memoryPool, size_t size)
{
    MemoryAllocator *m_MemoryAllocator = malloc(sizeof(MemoryAllocator));

    if(size % sizeof(size_t) != 0)
        size -= size % sizeof(size_t);

    m_MemoryAllocator->m_memoryPool = memoryPool;
    m_MemoryAllocator->m_size = size;

    /*((size_t*)m_MemoryAllocator->m_memoryPool) = 0;*/


    return m_MemoryAllocator;
}

void* MemoryAllocator_allocate(MemoryAllocator* allocator, size_t size)
{
    void* next_block_merge;
    void* current_address = allocator->m_memoryPool;
    while ((size_t)current_address < allocator->m_size + (size_t)allocator->m_memoryPool)
    {
        if(*(size_t*)((size_t)current_address + sizeof(size_t)) % sizeof(size_t) != 0)
        {
            current_address = next_block((void*)((size_t)current_address - 1));
            continue;
        }

        while (1)
        {
            if(*(size_t*)current_address == size)
            {
                current_address = (void*)((size_t)current_address + sizeof(size_t));
                current_address = (void*)((size_t)current_address + 1);
                return current_address;
            }

            if(*(size_t*)current_address > size)
            {
                void* new_block;
                size_t total_size = *(size_t*)current_address;
                *(size_t*)current_address = size;
                current_address = (void*)((size_t)current_address + sizeof(size_t));
                current_address = (void*)((size_t)current_address + 1);
                new_block = next_block((void*)((size_t)current_address - 1));
                *(size_t*)new_block = total_size - size - sizeof(size_t);

                return current_address;
            }

            next_block_merge = next_block(current_address);
            if((size_t)(next_block_merge) % sizeof(size_t) == 0)
            {
                *(size_t*)current_address = *(size_t*)current_address + *(size_t*)next_block_merge;
            }
        }
                

    }
    return 0;
}



size_t MemoryAllocator_free(MemoryAllocator* allocator, void* ptr)
{
    *((size_t*)allocator->m_memoryPool) = 0;

}
