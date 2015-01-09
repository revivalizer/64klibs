#pragma once

class ZMutex
{
public:
	ZMutex();
	~ZMutex();

	void Lock();
	void Unlock();

private:
	CRITICAL_SECTION mutex;
};

class ZScopedLock
{
public:

	ZScopedLock(ZMutex &mutex);
	ZScopedLock(ZMutex *mutex);
	~ZScopedLock();

	ZMutex* mutex;
};