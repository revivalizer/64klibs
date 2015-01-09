#pragma once

class ZGLWindowEvent : public align16
{
public:
};

class GEvent;

class ZGLWindow : public align16
{
public:
	ZGLWindow(void);
	~ZGLWindow(void);

	int Open(uint32_t width, uint32_t height, bool fullScreen);

	void HandleEvents();
	void SwapBuffers();

	#ifdef ENABLE_GUI
		bool GetNextEvent(GEvent& event);
	#endif

	//zvector<ZGLWindowEvent> eventQueue;
	//ZMutex                  eventQueueMutex;

	uint32_t     width, height;
	bool         isFullscreen;

	bool         isRunning;

	HINSTANCE    hInstance;
	HDC          hDC;
	HGLRC        hRC;
	HWND         hWnd;
	char*        wndclass;
};
