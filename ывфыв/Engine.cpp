#include "Engine.h"
#include <fstream>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <time.h>
#include "Matrix.h"

Engine::Engine(Window& wnd)
	:
	gfx(wnd.GetWindowWidth(), wnd.GetWindowHeight())
{
	Colors = wnd.GetColorBuffer();
	QueryPerformanceFrequency(&PerfCountFrequecyResult);
	PerfCountFrequency = (float)(PerfCountFrequecyResult.QuadPart);
	SetCursor(LoadCursor(nullptr, IDC_ARROW));
	//SleepIsGranular = (timeBeginPeriod(1) == TIMERR_NOERROR);
	//SetWindowTextA(wnd.GetCustomWindow(), "Winframework");
	wndf = &wnd;
	oldPx = wnd.mouse.GetPosX();
	oldPy = wnd.mouse.GetPosY();

	srand(time(nullptr));

	Matrix Xtrain(1, 19);
	Matrix Ytrain(1, 19);

	points = new Point[19]{};
	for (int x = 0; x < 19; x += 1) {
		int rx = 20 + 50 * x;
		points[x].x = rx;

		float ran = rand() % 100 - 50;
		float yy = (rx * c) + ran;
		points[x].y = yy;

		Xtrain.setValue(0, x, rx);
		Ytrain.setValue(0, x, yy);

	}

	w = (inverse(transpose(Xtrain) * Xtrain) * transpose(Xtrain) * Ytrain).getValue(0, 0);
}

Engine::~Engine()
{
}

void Engine::Run(Window& wnd)
{
	//Thread sleep to stop burning cycles
	LARGE_INTEGER LastCounter = EngineGetWallClock();

	LARGE_INTEGER WorkCounter = EngineGetWallClock();

	float WorkSecondsElapsed = EngineGetSecondsElapsed(LastCounter, WorkCounter);
	float SecondsElapsedForFrame = WorkSecondsElapsed;

	while (SecondsElapsedForFrame < FPSMS)
	{
		if (SleepIsGranular)
		{
			DWORD SleepMS = (DWORD)(1000.0f * (FPSMS - SecondsElapsedForFrame));
			Sleep(SleepMS);
		}
		SecondsElapsedForFrame = EngineGetSecondsElapsed(LastCounter, EngineGetWallClock());
	}



	cX = 1.0f / SecondsElapsedForFrame;
	Update(wnd);
	ComposeFrame();
	DrawHeader();

	LARGE_INTEGER EndCounter = EngineGetWallClock();
	LastCounter = EndCounter;
}

void Engine::Update(Window& wnd)
{
	if (wnd.kbd.KeyIsPressed('W'))
	{
		text = std::to_string(count);
		count++;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		textsize += 0.5f;

	}
	if (wnd.kbd.KeyIsPressed('A'))
	{

	}
	if (wnd.kbd.KeyIsPressed('R'))
	{
		delete[] points;
		Matrix Xtrain(1, 19);
		Matrix Ytrain(1, 19);

		points = new Point[19]{};
		for (int x = 0; x < 19; x += 1) {
			int rx = 20 + 50 * x;
			points[x].x = rx;

			float ran = rand() % 100 - 50;
			float yy = (rx * c) + ran;
			points[x].y = yy;

			Xtrain.setValue(0, x, rx);
			Ytrain.setValue(0, x, yy);

		}

		w = (inverse(transpose(Xtrain) * Xtrain) * transpose(Xtrain) * Ytrain).getValue(0, 0);
	}

	POINT cursorPos;
	GetCursorPos(&cursorPos);
	int mous_pos_x = wnd.mouse.GetPosX();
	int window_width = wnd.GetWindowWidth();
	if (wnd.mouse.LeftIsPressed() && wnd.mouse.GetPosY() < 25)
	{

		isDrag = true;
		if (mous_pos_x > window_width - 70 && mous_pos_x < window_width - 60) {
			CloseWindow(wnd.GetCustomWindow());
		}
		else if (mous_pos_x > window_width - 50 && mous_pos_x < window_width - 35) {
			if (!isMaximase) {
				int screenWidth = GetSystemMetrics(SM_CXSCREEN) + 1;
				int screenHeight = GetSystemMetrics(SM_CYSCREEN) + 1;
				gfx.setWindowWidth(screenWidth);
				gfx.setWindowHeight(screenHeight);
				wnd.MaximaseWindow(screenHeight, screenWidth);
				Colors = wnd.GetColorBuffer();
				window_width = screenWidth;
				isMaximase = true;
			}
			else {
				int screenWidth = 1080;
				int screenHeight = 720;
				gfx.setWindowWidth(screenWidth);
				gfx.setWindowHeight(screenHeight);
				wnd.MaximaseWindow(screenHeight, screenWidth);
				Colors = wnd.GetColorBuffer();
				window_width = screenWidth;
				HRGN hRgn = CreateRoundRectRgn(0, 0, screenWidth, screenHeight, 25, 25);
				SetWindowRgn(wnd.GetCustomWindow(), hRgn, true);
				isMaximase = false;
				wnd.MoveWnd(500, 50);
			}
			mous_pos_x = 0;
			window_width = 1920;
			newTap = false;
		}
		if (mous_pos_x > window_width - 25 && newTap) {
			PostQuitMessage(0);
		}
	}
	if (wnd.mouse.LeftIsPressed()) newTap = false;
	if (!wnd.mouse.LeftIsPressed()) {
		isDrag = false;
		newTap = true;
	}
	if (isDrag && !isMaximase) {
		wnd.MoveWnd(cursorPos.x - oldPx, cursorPos.y - oldPy);
	}
	oldPx = cursorPos.x;
	oldPy = cursorPos.y;
}

LARGE_INTEGER Engine::EngineGetWallClock() const
{
	LARGE_INTEGER Result;
	QueryPerformanceCounter(&Result);
	return Result;
}

float Engine::EngineGetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End) const
{
	float Result = ((float)(End.QuadPart - Start.QuadPart) / PerfCountFrequency);
	return Result;
}

void Engine::ComposeFrame()
{
	gfx.FillScreenFast(Colors, 20, 20, 20);
	gfx.DrawLinePrivate(Colors, 0, wndf->GetWindowWidth(), 25, 25, 90, 90, 90);


	for (int x = 20; x < 1000; x++)
		gfx.DrawPixel(Colors, x, wndf->GetWindowHeight() - 300, 90, 90, 90);

	for (int x = 20; x < 1000; x++)
		gfx.DrawPixel(Colors, x, wndf->GetWindowHeight() - (x * c) - 300, 255, 0, 0);

	for (int i = 0; i < 19; i++) {
		int x = points[i].x;
		int y = points[i].y;
		gfx.DrawPixel(Colors, x, wndf->GetWindowHeight() - y - 300, 0, 0, 255);
		gfx.DrawElipsSmooth(Colors, 5, x, wndf->GetWindowHeight() - y - 300, 0, 0, 255);
	}

	for (int x = 20; x < 1000; x++)
		gfx.DrawPixel(Colors, x, wndf->GetWindowHeight() - (x * w) - 300, 0, 255, 0);

}

void Engine::DrawHeader()
{
	Text_rend tr;
	tr.renderText(Colors, wndf->GetWindowWidth(), wndf->GetWindowHeight(), 20, "AM framework", 5, 5, 90, 90, 90);
	tr.renderText(Colors, wndf->GetWindowWidth(), wndf->GetWindowHeight(), 20, "X", wndf->GetWindowWidth() - 25, 5, 90, 90, 90);

	gfx.DrawLinePrivate(Colors, 0, wndf->GetWindowWidth(), 25, 25, 90, 90, 90);

	gfx.DrawRectanclePrivate(Colors, wndf->GetWindowWidth() - 50, wndf->GetWindowWidth() - 35, 5, 20, 90, 90, 90);
	gfx.DrawRectanclePrivate(Colors, wndf->GetWindowWidth() - 48, wndf->GetWindowWidth() - 37, 7, 18, 20, 20, 20);

	gfx.DrawRectanclePrivate(Colors, wndf->GetWindowWidth() - 70, wndf->GetWindowWidth() - 60, 12, 14, 90, 90, 90);
}
