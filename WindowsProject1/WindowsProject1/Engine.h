#pragma once
#include "Window.h"
#include "Graphics.h"
#include <string>
#include <thread>
#include "FPScontroller.h"

class Engine
{
public:
	Engine(class Window& wnd);
	Engine(const Engine&) = delete;
	Engine operator=(const Engine&) = delete;
	~Engine();

	void Run(class Window& wnd);
private:
	void ComposeFrame();
	void Update(class Window& wnd);
	LARGE_INTEGER EngineGetWallClock() const;
	float EngineGetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End) const;
private:
	
	int* Colors;
	FPScontroller ft;
	Graphics gfx;
private:
	LARGE_INTEGER PerfCountFrequecyResult;
	bool SleepIsGranular = true;
	float PerfCountFrequency;
	const float FPSMS = 1.0f / 60.0f;
	float tick = 0;

	float cX = 0;
	
private:
	//Game stuff here
	float speed = 0.8f;
	float r_speed = 1;
};