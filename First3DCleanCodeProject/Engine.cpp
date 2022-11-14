#include "Engine.h"

Engine::Engine(Window& wnd)
	:
	gfx(wnd.GetWindowWidth(), wnd.GetWindowHeight())
{
	Colors = wnd.GetColorBuffer();
	QueryPerformanceFrequency(&PerfCountFrequecyResult);
	PerfCountFrequency = (float)(PerfCountFrequecyResult.QuadPart);
	//SleepIsGranular = (timeBeginPeriod(1) == TIMERR_NOERROR);
	SetWindowTextA(wnd.GetCustomWindow(), "Winframework");
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

	LARGE_INTEGER EndCounter = EngineGetWallClock();
	LastCounter = EndCounter;
}

void Engine::Update(Window& wnd)
{
	
	if (wnd.kbd.KeyIsPressed('W'))
	{
		playerx += 3;
	}
	if (wnd.kbd.KeyIsPressed('S'))
	{
		playerx -= 3;
	}
	if (wnd.kbd.KeyIsPressed('A'))
	{
		
	}
	if (wnd.kbd.KeyIsPressed('D'))
	{
		
	}
	
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
	gfx.ClearScreenSuperFast(Colors);

	int linex = 100;
	int line = 720;
	int distance;
	if (linex > playerx) distance = linex - playerx;
	else distance = playerx - linex;
	float render = 20 * line / distance;
	gfx.DrawRectancle(Colors, gfx.GetWindowWidth() / 2 - render / 2, gfx.GetWindowWidth() / 2 + render / 2,
		gfx.GetWindowHeight() / 2 - render / 2, gfx.GetWindowHeight() / 2 + render / 2, 200, 200, 30);
	gfx.DrawLine(Colors, 1, gfx.GetWindowWidth() / 2 - render / 2, 1, gfx.GetWindowHeight() / 2 - render / 2, 30, 100, 200);
	gfx.DrawLine(Colors, 1, gfx.GetWindowWidth() / 2 - render / 2, gfx.GetWindowHeight(), gfx.GetWindowHeight() / 2 + render / 2, 30, 100, 200);
	

}
