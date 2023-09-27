#include "Engine.h"

Engine::Engine(Window& wnd)
	:
	gfx(wnd.GetWindowWidth(), wnd.GetWindowHeight())
{
	Colors = wnd.GetColorBuffer();
	QueryPerformanceFrequency(&PerfCountFrequecyResult);
	PerfCountFrequency = (float)(PerfCountFrequecyResult.QuadPart);
	//SleepIsGranular = (timeBeginPeriod(1) == TIMERR_NOERROR);
	SetWindowTextA(wnd.GetCustomWindow(), "Ray-Tracing");

	}

Engine::~Engine()
{
	//delete map;
}

void Engine::Run(Window& wnd)
{
	std::thread t(&Engine::ComposeFrame, this);
	//ComposeFrame();

	float dt = ft.Go();
	cX += dt;
	std::chrono::duration<float> SleepTime(FPSMS - cX);

	if (cX < FPSMS) {
		std::this_thread::sleep_for(SleepTime);
	}
	else {
		cX = 0.0f;
	}

	std::string str = std::to_string(1.0f / dt);
	LPCSTR name = str.c_str();
	SetWindowTextA(wnd.GetCustomWindow(), str.c_str());

	//SecondsElapsedForFrame = EngineGetSecondsElapsed(LastCounter, EngineGetWallClock());


	Update(wnd);
	tick += 1;
	if (tick > 144) tick = 0;

	t.join();
}

void Engine::Update(Window& wnd)
{
	

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

	

	gfx.DrawCircle16(Colors, 200, 200, 200, 55, 10, 255, 255);
	gfx.DrawCircle16(Colors, 300, 350, 100, 255, 5, 55, 125);
	gfx.DrawCircle16(Colors, 410, 310, 120, 75, 255, 55, 50);
	

	
	
}
