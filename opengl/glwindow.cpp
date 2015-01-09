#include "pch.h"
#include "glwindow.h"
#include "libs/imgui/types.h"
#include "libs/imgui/event.h"

// Much of this from Ferris' 4k framework, which takes a lot from iq

static const PIXELFORMATDESCRIPTOR pfd =
{
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	32,
	0, 0, 0, 0, 0, 0, 8, 0,
	0, 0, 0, 0, 0,  // accum
	32,             // zbuffer
	0,              // stencil!
	0,              // aux
	PFD_MAIN_PLANE,
	0, 0, 0, 0
};

static LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	// Save us from powerdowns and screensavers
	if( uMsg==WM_SYSCOMMAND && (wParam==SC_SCREENSAVE || wParam==SC_MONITORPOWER) )
		return( 0 );

	// Quit on escape
	if( uMsg==WM_CLOSE || uMsg==WM_DESTROY || (uMsg==WM_KEYDOWN && wParam==VK_ESCAPE) )
	{
		PostQuitMessage(0);
		return( 0 );
	}

	if( uMsg==WM_CHAR )
	{
		if( wParam==VK_ESCAPE )
		{
			PostQuitMessage(0);
			return( 0 );
		}
	}

	return( DefWindowProc(hWnd,uMsg,wParam,lParam) );
}

ZGLWindow::ZGLWindow()
{
	isRunning = true;
}

int ZGLWindow::Open(uint32_t width, uint32_t height, bool fullScreen)
{
	unsigned int	PixelFormat;
    DWORD			dwExStyle, dwStyle;
    DEVMODE			dmScreenSettings;
    RECT			rect;

    WNDCLASS		wc;

	this->isFullscreen = fullScreen;
	this->width = width;
	this->height = height;

	hInstance = GetModuleHandle(0);
    wndclass = "TPTGRNQRZRRVLPNQ";

    zzeromem( &wc, sizeof(WNDCLASS) );
    wc.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = wndclass;
	
    if( !RegisterClass(&wc) )
        return( 0 );

    if( isFullscreen )
    {
        dmScreenSettings.dmSize       = sizeof(DEVMODE);
        dmScreenSettings.dmFields     = DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmPelsWidth  = width;
        dmScreenSettings.dmPelsHeight = height;
        if( ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
            return( 0 );
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle   = WS_VISIBLE | WS_POPUP;// | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		ShowCursor( 0 );
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
        dwStyle   = WS_VISIBLE | WS_CAPTION | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU;
    }

    rect.left   = 0;
    rect.top    = 0;
    rect.right  = width;
    rect.bottom = height;
    AdjustWindowRect( &rect, dwStyle, 0 );

    hWnd = CreateWindowEx( dwExStyle, wc.lpszClassName, TEXT(WINDOW_TITLE), dwStyle,
                               (GetSystemMetrics(SM_CXSCREEN)-rect.right+rect.left)>>1,
                               (GetSystemMetrics(SM_CYSCREEN)-rect.bottom+rect.top)>>1,
                               rect.right-rect.left, rect.bottom-rect.top, 0, 0, hInstance, 0 );
    if( !hWnd )
        return( 0 );

    if( (hDC=GetDC(hWnd))==0 )
        return( 0 );

	// Clear to black
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	FillRect(hDC, &rect, brush);
	DeleteObject(brush);

    if( (PixelFormat=ChoosePixelFormat(hDC,&pfd))==0 )
        return( 0 );

    if( !SetPixelFormat(hDC,PixelFormat,&pfd) )
        return( 0 );

    if( (hRC=wglCreateContext(hDC))==0 )
        return( 0 );

    if( !wglMakeCurrent(hDC,hRC) )
        return( 0 );
    
    return( 1 );
}

ZGLWindow::~ZGLWindow(void)
{
	if( hRC )
	{
		wglMakeCurrent( 0, 0 );
		wglDeleteContext( hRC );
	}

	if( hDC  ) ReleaseDC( hWnd, hDC );
	if( hWnd ) DestroyWindow( hWnd );

	UnregisterClass( wndclass, hInstance );

	if( isFullscreen )
	{
		ChangeDisplaySettings( 0, 0 );
		ShowCursor( 1 );
	}
}

void ZGLWindow::HandleEvents()
{
	MSG msg;

	while( PeekMessage(&msg,0,0,0,PM_REMOVE) )
	{
		if( msg.message==WM_QUIT )
			isRunning = false;

		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
}

#ifdef ENABLE_GUI
bool ZGLWindow::GetNextEvent(GEvent& event)
{
	MSG msg;

	uint32_t clickCount = 1;
	uint32_t modifiers = 0;
	GEventMouseButton button = kGEventMouseButtonNone;

	while( PeekMessage(&msg,0,0,0,PM_REMOVE) )
	{
		switch (msg.message)
		{
			// Mouse events
			// Currently only support for right and left buttons. Could also support MBUTTON and XBUTTON (XBUTTON1 & XBUTTON2) and scroll wheel
			// We utilize some clever passthrough the various cases
			case WM_LBUTTONDBLCLK:
			{
				if (button==kGEventMouseButtonNone)
					button = kGEventMouseButtonLeft;
			}
			case WM_RBUTTONDBLCLK:
			{
				if (button==kGEventMouseButtonNone)
					button = kGEventMouseButtonRight;

				clickCount = 2;
			}
			case WM_LBUTTONDOWN:
			{
				if (button==kGEventMouseButtonNone)
					button = kGEventMouseButtonLeft;
			}
			case WM_RBUTTONDOWN:
			{
				if (button==kGEventMouseButtonNone)
					button = kGEventMouseButtonRight;

				// Get modifiers
				if (msg.wParam & MK_CONTROL)
					modifiers |= kGEventModifierControl;
				if (msg.wParam & MK_SHIFT)
					modifiers |= kGEventModifierShift;
				// added to achieve information from the ALT button
				if (GetKeyState (VK_MENU) < 0)
					modifiers |= kGEventModifierAlt;

				GPoint pos((GCoord)(short)LOWORD(msg.lParam), (GCoord)(short)HIWORD(msg.lParam));

				event.type = kGEventMouseDown;
				event.button = button;
				event.modifiers = modifiers;
				event.clickCount = clickCount;
				event.pos = pos;

				SetCapture(hWnd);

				return true;
			}
			case WM_MOUSEMOVE:
			{
				GPoint pos((GCoord)(short)LOWORD(msg.lParam), (GCoord)(short)HIWORD(msg.lParam));

				// Get modifiers
				if (msg.wParam & MK_CONTROL)
					modifiers |= kGEventModifierControl;
				if (msg.wParam & MK_SHIFT)
					modifiers |= kGEventModifierShift;
				// added to achieve information from the ALT button
				if (GetKeyState (VK_MENU) < 0)
					modifiers |= kGEventModifierAlt;

				event.type = kGEventMouseMove;
				event.modifiers = modifiers;
				event.pos = pos;

				return true;
			}
			case WM_LBUTTONUP:
			{
				if (button==kGEventMouseButtonNone)
					button = kGEventMouseButtonLeft;
			}
			case WM_RBUTTONUP:
			{
				if (button==kGEventMouseButtonNone)
					button = kGEventMouseButtonRight;

				// Get modifiers
				if (msg.wParam & MK_CONTROL)
					modifiers |= kGEventModifierControl;
				if (msg.wParam & MK_SHIFT)
					modifiers |= kGEventModifierShift;
				// added to achieve information from the ALT button
				if (GetKeyState (VK_MENU) < 0)
					modifiers |= kGEventModifierAlt;

				GPoint pos((GCoord)(short)LOWORD(msg.lParam), (GCoord)(short)HIWORD(msg.lParam));

				event.type = kGEventMouseUp;
				event.button = button;
				event.modifiers = modifiers;
				event.pos = pos;

				ReleaseCapture();

				return true;
			}

			default:
			{
				if (msg.message==WM_QUIT)
					isRunning = false;

				TranslateMessage( &msg );
				DispatchMessage( &msg );

				break;
			}
		}
	}

	return false;
}
#endif

void ZGLWindow::SwapBuffers()
{
	::SwapBuffers(hDC);
}
