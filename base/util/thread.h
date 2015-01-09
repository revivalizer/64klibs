#pragma once

#ifdef WIN32
	#undef Yield
#else
	#include <pthread.h>
#endif

class ZThread : public align16
{
	public:
		ZThread();
		virtual ~ZThread();

		void Start();
		void Cancel();

		static void Yield();

		void Terminate();

	private:
		#ifdef _WIN32
			DWORD					threadId;
			HANDLE					threadHandle;
		#else
			pthread_t 				thread;
		#endif

	protected:
		// Overload this with running function
		virtual void Run() {}

		// State
		bool isRunning;
		bool shouldCancel;

	// Must friend start functions
	#ifdef WIN32
		friend DWORD WINAPI ThreadStart(LPVOID pArg);
	#else
		friend void* ThreadStart(void* pArg);
	#endif

};

