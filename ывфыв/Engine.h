#pragma once
#include "Window.h"
#include "Graphics.h"
#include "Timer.h"
#include <string>
#include <thread>
#include <fstream>
#include <vector>
#include "text_render.h"
#include <string>


class Point {
public:
	Point(float x, float y) : x(x), y(y) {};
	Point() {};
	float x = 0;
	float y = 0;
};

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
	void DrawHeader();
	void Update(class Window& wnd);
	LARGE_INTEGER EngineGetWallClock() const;
	float EngineGetSecondsElapsed(LARGE_INTEGER Start, LARGE_INTEGER End) const;
private:
	Graphics gfx;
	int* Colors;
	Timer ft;

private:
	LARGE_INTEGER PerfCountFrequecyResult;
	bool SleepIsGranular = true;
	float PerfCountFrequency;
	const float FPSMS = 1.0f / 144.0f;

	Window* wndf = nullptr;
	float cX = 0;
private:
	std::string text = "";
	int count = 0;
	int oldPx;
	int oldPy;


	int dragX = 0;
	int dragY = 0;
	bool isDrag = false;
private:
	float c = 0.1f;
	float b = 0.15f;

	float w = 0.0f;
	Point* points = nullptr;

	float textsize = 20.0f;
	bool isMaximase = false;
	bool newTap = true;
};

