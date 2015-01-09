#pragma once

template <class T>
class ZStack : public align16
{
public:
	ZStack(size_t size);
	~ZStack(void);

	void     Push(const T& o);
	T&       Pop(void);
	void     Pop(size_t number);
	T&       Get(int32_t offset) const;
	T&       Top() const;
	uint32_t Height() { return top; }
	void     Reset();

private:
	T* data;
	uint32_t top;
	uint32_t size;
};

template <class T>
void ZStack<T>::Reset()
{
	top = 0;
}

template <class T>
T& ZStack<T>::Get(int32_t offset) const
{
	int32_t pos = (int32_t)top + offset;

	ZASSERT((pos >= 0) && (pos < (int32_t)size))

	return data[pos];
}

template <class T>
T& ZStack<T>::Top() const
{
	return Get(-1);
}


template <class T>
void ZStack<T>::Pop( size_t number )
{
	ZASSERT(top-number >= 0)

	top -= number;
}

template <class T>
T& ZStack<T>::Pop( void )
{
	ZASSERT(top > 0);

	return data[--top];
}

template <class T>
void ZStack<T>::Push( const T& o )
{
	ZASSERT(top < size-1);
	
	data[top++] = o;
}

template <class T>
ZStack<T>::ZStack(size_t size) : align16()
	, data(new T[size])
	, top(0)
	, size(size)
{
}

template <class T>
ZStack<T>::~ZStack(void)
{
	delete[] data;
}
