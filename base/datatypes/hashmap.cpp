#include "pch.h"

hash_t ZHash( const char* str )
{
	// The fnv 1a hash
	// http://www.isthe.com/chongo/tech/comp/fnv/
	unsigned const char* s = (unsigned const char*)str;

	auto hash = init_hash();

	while (*s)
	{
		update_hash(hash, *s);
		s++;
	}

	return hash;
}

hash_t ZHash(uint8_t v)
{
	auto hash = init_hash();
	update_hash(hash, v);
	return hash;
}

hash_t ZHash(uint16_t v)
{
	auto hash = init_hash();
	update_hash(hash, v);
	return hash;
}

hash_t ZHash(uint32_t v)
{
	auto hash = init_hash();
	update_hash(hash, v);
	return hash;
}

hash_t ZHash(int8_t v)
{
	auto hash = init_hash();
	update_hash(hash, v);
	return hash;
}

hash_t ZHash(int16_t v)
{
	auto hash = init_hash();
	update_hash(hash, v);
	return hash;
}

hash_t ZHash(int32_t v)
{
	auto hash = init_hash();
	update_hash(hash, v);
	return hash;
}
