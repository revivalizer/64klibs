#pragma once

// Originally from here: http://www.codeproject.com/Articles/64111/Building-a-Quick-and-Handy-Reference-Counting-Clas

// Base class for all classes that support reference counting
class ZReferenceCount
{
public:
	ZReferenceCount() : refCount(0) {}
	virtual ~ZReferenceCount() {}

	virtual void Retain() const {++refCount;}
	
	virtual void Release() const
	{
		ZASSERT(refCount > 0);
		--refCount;

		if(refCount == 0) {delete (ZReferenceCount *)this;}
	}

protected:
	mutable int32_t refCount;
};

// A reference counting-managed pointer for classes derived from RCBase which can be used as C pointer
template <class T>
class ZSmartPtr
{
public:
	// Construct using a C pointer
	// e.g. ZSmartPoint< T > x = new T();
	ZSmartPtr(T* ptr = nullptr)
		: mPtr(ptr)
	{
		if(ptr != nullptr) {ptr->Retain();}
	}

	// Copy constructor
	ZSmartPtr(const ZSmartPtr &ptr)
		: mPtr(ptr.mPtr)
	{
		if(mPtr != nullptr) {mPtr->Retain();}
	}

	~ZSmartPtr()
	{
		if(mPtr != nullptr) {mPtr->Release();}
	}

	// Assign a pointer
	// e.g. x = new T();
	ZSmartPtr &operator=(T* ptr)
	{
		// The following grab and release operations have to be performed
		// in that order to handle the case where ptr == mPtr
		// (See comment below by David Garlisch)
		if(ptr != nullptr) { ptr->Retain(); }
		if(mPtr != nullptr) { mPtr->Release(); }
		mPtr = ptr;
		return (*this);
	}

	// Assign another ZSmartPtr
	ZSmartPtr &operator=(const ZSmartPtr &ptr)
	{
		return (*this) = ptr.mPtr;
	}

	// Retrieve actual pointer
	T* get() const
	{
		return mPtr;
	}

	// Some overloaded operators to facilitate dealing with an RCPtr as a conventional C pointer.
	// Without these operators, one can still use the less transparent get() method to access the pointer.
	T* operator->() const                  { return mPtr; }                // x->member
	T &operator*() const                   { return *mPtr; }               // *x, (*x).member
	operator T*() const                    { return mPtr; }                // T* y = x;
	operator bool() const                  { return mPtr != nullptr; }     // if(x) {/*x is not nullptr*/}
	bool operator==(const ZSmartPtr &ptr)  { return mPtr == ptr.mPtr; }
	bool operator==(const T *ptr)          { return mPtr == ptr; }

private:
	T *mPtr;	//Actual pointer
};
