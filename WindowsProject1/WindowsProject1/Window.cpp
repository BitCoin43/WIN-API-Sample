#include "Window.h"
#include <assert.h>

Window::Window(int width, int height, HINSTANCE hInstance)
	:
	hInst(hInstance),
	WindowWidth(width),
	WindowHeight(height)
{
	ResizeDIB(WindowWidth, WindowHeight);
	WNDCLASSEXA wc = {};
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = StartMessage;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;

	RegisterClassExA(&wc);
	// create window & get hWnd
	RECT wr;
	wr.left = 0;
	wr.right = WindowWidth + wr.left;
	wr.top = 36;
	wr.bottom = WindowHeight + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hwnd = CreateWindowExA(0, pClassName, "Windows Framework", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		wr.left, wr.top, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, hInst, this);

	ShowWindow(hwnd, SW_SHOWDEFAULT);
	//UpdateWindow(hwnd);
}

Window::~Window()
{
	UnregisterClassA(pClassName, hInst);
	delete[] Colors;
	Colors = nullptr;
}

bool Window::RunMessageLoop()
{
	MSG msg;
	if (PeekMessageA(
		&msg,
		0,
		0,
		0,
		PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;
		}
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
	HDC surface = GetDC(hwnd);
	RECT rc;
	GetClientRect(hwnd, &rc);
	UpdateWindowBuffer(surface, rc.right - rc.left, rc.bottom - rc.top);
	ReleaseDC(hwnd, surface);
	return true;
}

HWND Window::GetCustomWindow() const
{
	return hwnd;
}

int Window::GetWindowWidth() const
{
	return WindowWidth;
}

int Window::GetWindowHeight() const
{
	return WindowHeight;
}

void Window::ClearScreenSuperFast()
{
	memset(Colors, 0, WindowWidth * WindowHeight * 4);
}

void Window::ResizeDIB(int BitmapWidth, int BitmapHeight)
{
	if (Colors)
	{
		delete[] Colors;
		Colors = nullptr;
	}
	bmInfo.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmInfo.bmiHeader.biWidth = BitmapWidth;
	bmInfo.bmiHeader.biHeight = -BitmapHeight;
	bmInfo.bmiHeader.biPlanes = 1;
	bmInfo.bmiHeader.biBitCount = 32;
	bmInfo.bmiHeader.biCompression = BI_RGB;

	Colors = new int[BitmapWidth * BitmapHeight];

	ClearScreenSuperFast();
}

void Window::UpdateWindowBuffer(HDC hdc, int BitmapWidth, int BitmapHeight)
{
	StretchDIBits(
		hdc,
		0,
		0,
		WindowWidth,
		WindowHeight,
		0,
		0,
		BitmapWidth,
		BitmapHeight,
		Colors,
		&bmInfo,
		DIB_RGB_COLORS,
		SRCCOPY
	);

}

int* Window::GetColorBuffer()
{
	return Colors;
}

LRESULT Window::StartMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		// sanity check
		assert(pWnd != nullptr);
		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::MessageSetup));
		// forward message to window class handler
		return pWnd->HandleMessage(hwnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}

LRESULT Window::MessageSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// retrieve ptr to window class
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	// forward message to window class handler
	return pWnd->HandleMessage(hwnd, msg, wParam, lParam);
}

LRESULT Window::HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	case WM_QUIT:
	{
		PostQuitMessage(0);
	}break;
	case WM_SIZE:
	{

	}break;
	case WM_KILLFOCUS:
	{

	}break;
	// ************ KEYBOARD MESSAGES ************ //
	}
	return DefWindowProcA(hwnd, msg, wParam, lParam);
}