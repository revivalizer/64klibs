#pragma once

typedef uint32_t hash_t;

inline hash_t init_hash()
{
	return 2166136261;
}

inline void update_hash(hash_t& h, uint8_t v)
{
	h ^= (hash_t)v;
	h *= 16777619;
}

inline void update_hash(hash_t& h, uint16_t v)
{
	update_hash(h, (uint8_t)(v >> 0));
	update_hash(h, (uint8_t)(v >> 8));
}

inline void update_hash(hash_t& h, uint32_t v)
{
	update_hash(h, (uint16_t)(v >> 0));
	update_hash(h, (uint16_t)(v >> 16));
}

inline void update_hash(hash_t& h, int8_t v)
{
	update_hash(h, uint8_t(v));
}

inline void update_hash(hash_t& h, int16_t v)
{
	update_hash(h, uint16_t(v));
}

inline void update_hash(hash_t& h, int32_t v)
{
	update_hash(h, uint32_t(v));
}

