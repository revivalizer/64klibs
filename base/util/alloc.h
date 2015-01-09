void* zalloc(size_t size);
void* zrealloc(void* mem, uint32_t amount);
void zfree(void* p);

void* zalignedalloc(size_t size, size_t align);
void* zalignedrealloc(void* mem, size_t size, size_t align);
void zalignedfree(void* p);

