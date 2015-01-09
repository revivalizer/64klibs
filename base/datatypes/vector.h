#pragma once

template <class T>
class zvector
{
public:
	zvector(size_t allocEntries = 32)
		: allocEntries(0)
		, numEntries(0)
		, data(nullptr)
	{
		realloc(allocEntries);
	}

	~zvector(void)
	{
		if (data)
			//delete data;
			zalignedfree(data);
	};

	size_t size() const { return numEntries; }

	void push_back(const T& v)
	{
		if (numEntries==allocEntries)
			realloc(allocEntries*2);

		data[numEntries] = v;
		numEntries++;
	}

	T& pop_back()
	{
		numEntries--;
		return data[numEntries];
	}

	const T& operator[](size_t i) const
	{
		return data[i];
	}

	T& operator[](size_t i)
	{
		return data[i];
	}

	void clear()
	{
		numEntries = 0;
	}

	void reset(uint32_t num)
	{
		clear();
		for (uint32_t i=0; i<num; i++)
			push_back(T());
	}

	size_t numEntries;
	size_t allocEntries;

	T* data;
private:

	void realloc(size_t newsize)
	{
		//T* newdata = (T*)new uint8_t[newsize*sizeof(T)];
		T* newdata = (T*)zalignedalloc(newsize*sizeof(T), 16);
		zmemcpy(newdata, data, sizeof(T)*allocEntries);
		if (data)
			//delete data;
			zalignedfree(data);
		data = newdata;
		allocEntries = newsize;
	}
};

