#pragma once
#include "WinLib.h"

class Window
{
public:
	Window(int width, int height, HINSTANCE hInstance);
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;
	~Window();
	bool RunMessageLoop();
	HWND GetCustomWindow() const;
	int GetWindowWidth() const;
	int GetWindowHeight()const;
private:
	static LRESULT CALLBACK StartMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK MessageSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void ResizeDIB(int BitmapWidth, int BitmapHeight);
	void ClearScreenSuperFast();


public:
	void UpdateWindowBuffer(HDC hdc, int BitmapWidth, int BitmapHeight);
	int* GetColorBuffer();
	void RunLoop();
private:
	HINSTANCE hInst;
	HWND hwnd = nullptr;
	BITMAPINFO bmInfo = {};
	int* Colors = nullptr;
	int WindowWidth;
	int WindowHeight;
	LPSTR pClassName = new TCHAR[1];

	bool run = 1;
public:
	Keyboard kbd;
	Mouse mouse;
};