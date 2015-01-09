#pragma once

template <class T, class U>
class zpair 
{
public:
	zpair(T first, U second)
		: first(first)
		, second(second)
	{
	}

	T first;
	U second;
};

template <class T, class U>
class zhashmap : public align16
{
public:
	zhashmap(uint32_t numBins)
		: bins(numBins)
		, numBins(numBins)
	{
		bins.reset(numBins);

		for (uint32_t i=0; i<numBins; i++)
		{
			bins[i] = new zlist<zpair<T, U> >;
		}
	}

	void insert(T t, U u)
	{
		uint32_t bin = ZHash(t) % numBins;
		bins[bin]->push_front(zpair<T, U>(t, u));
	}

	bool find(T t, U* u)
	{
		uint32_t bin = ZHash(t) % numBins;

		for (auto *current = bins[bin]->head, *sentinel = bins[bin]->get_sentinel(); current!=sentinel; current=current->next)
		{
			if (ZHashCompare(t, current->value.first))
			{
				*u = current->value.second;
				return true;
			}
		}
		
		return false;
	}

	zvector<zlist<zpair<T, U> >* > bins;
	uint32_t numBins;
};

hash_t ZHash(const char* str);
hash_t ZHash(uint8_t v);
hash_t ZHash(uint16_t v);
hash_t ZHash(uint32_t v);
hash_t ZHash(int8_t v);
hash_t ZHash(int16_t v);
hash_t ZHash(int32_t v);

inline bool ZHashCompare(const char* str1, const char* str2)
{
	return zstrequal(str1, str2);
}

inline bool ZHashCompare(uint8_t v1, uint8_t v2)
{
	return v1==v2;
}

inline bool ZHashCompare(uint16_t v1, uint16_t v2)
{
	return v1==v2;
}

inline bool ZHashCompare(uint32_t v1, uint32_t v2)
{
	return v1==v2;
}

inline bool ZHashCompare(int8_t v1, int8_t v2)
{
	return v1==v2;
}

inline bool ZHashCompare(int16_t v1, int16_t v2)
{
	return v1==v2;
}

inline bool ZHashCompare(int32_t v1, int32_t v2)
{
	return v1==v2;
}

