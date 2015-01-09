#include "pch.h"

// Adapted from: http://flyeater.wordpress.com/2010/11/29/memory-allocation-and-data-alignment-custom-mallocfree/

void* zalloc(size_t size)
{
	return HeapAlloc(GetProcessHeap(), 0, size);
}

void zfree(void* p)
{
	HeapFree(GetProcessHeap(), 0, p);
}

void* zrealloc(void* mem, uint32_t amount)
{
	return HeapReAlloc(GetProcessHeap(), 0, (unsigned char*)mem, amount );
}

void* zalignedrealloc(void* mem, size_t size, size_t align)
{
    /* Allocate necessary memory area
     * client request - size parameter -
     * plus area to store the address
     * of the memory returned by standard
     * malloc().
     */
    void *ptr = *((void**)((unsigned int)mem - sizeof(void*)));
    void *p = zrealloc(ptr, size + align - 1 + sizeof(void*));
     
    if (p != nullptr) {
        /* Address of the aligned memory according to the align parameter*/
        ptr = (void*) (((unsigned int)p + sizeof(void*) + align -1) & ~(align-1));
        /* store the address of the malloc() above
         * at the beginning of our total memory area.
         * You can also use *((void **)ptr-1) = p
         * instead of the one below.
         */
        *((void**)((unsigned int)ptr - sizeof(void*))) = p;
        /* Return the address of aligned memory */
        return ptr;
    }
    return nullptr;
}


void* zalignedalloc(size_t size, size_t align)
{
    /* Allocate necessary memory area
     * client request - size parameter -
     * plus area to store the address
     * of the memory returned by standard
     * malloc().
     */
    void *ptr;
    void *p = zalloc(size + align - 1 + sizeof(void*));
     
    if (p != nullptr) {
        /* Address of the aligned memory according to the align parameter*/
        ptr = (void*) (((unsigned int)p + sizeof(void*) + align -1) & ~(align-1));
        /* store the address of the malloc() above
         * at the beginning of our total memory area.
         * You can also use *((void **)ptr-1) = p
         * instead of the one below.
         */
        *((void**)((unsigned int)ptr - sizeof(void*))) = p;
        /* Return the address of aligned memory */
        return ptr;
    }
    return nullptr;
}

void zalignedfree(void* p)
{
    /* Get the address of the memory, stored at the
     * start of our total memory area. Alternatively,
     * you can use void *ptr = *((void **)p-1) instead
     * of the one below.
     */

    if (nullptr==p)
      return; // do nothing if trying to free null ptr

    void *ptr = *((void**)((unsigned int)p - sizeof(void*)));
    zfree(ptr);
    return;
}