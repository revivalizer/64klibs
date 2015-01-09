// Inheriting from this class extends the child class with new/delete operators that ensure that it is allocated on 16 byte boundaries

#pragma warning(push)
#pragma warning(disable:4324)
__declspec(align(16)) class align16
{
public:
	void *__cdecl operator new(size_t size)
	{
		return zalignedalloc(size, 16);
	}

	void __cdecl operator delete(void *p)
	{
		zalignedfree(p);
	}

	void *__cdecl operator new[](size_t size)
	{
		return zalignedalloc(size, 16);
	}

	void __cdecl operator delete[](void *p)
	{
		zalignedfree(p);
	}
};
#pragma warning(pop)
