#include "pch.h"

// Startup functions
#ifdef WIN32
	DWORD WINAPI ThreadStart(LPVOID pArg)
	{
		ZThread *thread = (ZThread*)pArg;
		thread->isRunning = true;
		SetThreadPriority(thread->threadHandle, THREAD_PRIORITY_LOWEST);
		thread->Run();
		thread->isRunning = false;
		CloseHandle(thread->threadHandle);
		thread->threadHandle = NULL;
		thread->threadId = NULL;
		return 0;
	}
#else
	#include <unistd.h>
	#include <sched.h>
	void* ThreadStart(void* pArg)
	{
		ZThread* thread = (ZThread*)pArg;
		thread->isRunning = true;
		thread->Run();
		thread->isRunning = false;
		thread->thread = NULL;
		return 0;
	}
#endif

ZThread::ZThread() : align16()
, isRunning(false)
, shouldCancel(false)
{
#ifdef WIN32
	threadId = NULL;
#endif
}

ZThread::~ZThread()
{
	if (isRunning)
		Cancel();
}

void ZThread::Start()
{
	ZASSERT(!isRunning);

	#ifdef _WIN32
		threadHandle = CreateThread( NULL, NULL, ThreadStart, (void*)this, NULL, &threadId );
		if (!threadHandle)
		{
			//zerror("Fatal error: Couldn't create thread.\n");
		}
	#else
		if(pthread_create(&thread, 0, ThreadStart, (void*)this) != 0)
		{
			reportError("Fatal error: Couldn't create thread.\n");
		}
	#endif
}

void ZThread::Cancel()
{
	// Return if not running
	if (!isRunning)
		return;

	// Tell thread to cancel
	shouldCancel = true;

	// Block until thread isn't running
	while (isRunning)
		ZThread::Yield();

	shouldCancel = false;
}

void ZThread::Yield()
{
#ifdef WIN32
	SwitchToThread();
#else
	sched_yield();
#endif
}

void ZThread::Terminate()
{
	TerminateThread(threadHandle, 0);
}


