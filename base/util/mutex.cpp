#include "pch.h"

ZMutex::ZMutex()
{
	::InitializeCriticalSection(&mutex);
}

ZMutex::~ZMutex()
{
	::DeleteCriticalSection(&mutex);
}

void ZMutex::Lock()
{
	::EnterCriticalSection(&mutex);
}

void ZMutex::Unlock()
{
	::LeaveCriticalSection(&mutex);
}

ZScopedLock::ZScopedLock(ZMutex *mutex)
{
	this->mutex = mutex;
	this->mutex->Lock();
}

ZScopedLock::ZScopedLock(ZMutex &mutex)
{
	this->mutex = &mutex;
	this->mutex->Lock();
}

ZScopedLock::~ZScopedLock()
{
	if (mutex)
		mutex->Unlock();
}