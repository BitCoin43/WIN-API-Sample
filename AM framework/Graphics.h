#pragma once
#include <ft2build.h>
#include <freetype/freetype.h>
#include FT_FREETYPE_H
#include <string>

class Graphics
{
public:
	Graphics(int WindowWidth, int WindowHeight);
	Graphics(const Graphics&) = delete;
	Graphics operator=(const Graphics&) = delete;
	~Graphics();

	void FillScreenFast(int* Colors, unsigned char r, unsigned char g, unsigned char b);
	void ClearScreenSuperFast(int* Colors);
	void DrawPixel(int* Colors, int x, int y, unsigned char r, unsigned char g, unsigned char b);
	void DrawPixelPrivate(int* Colors, int x, int y, unsigned char r, unsigned char g, unsigned char b);
	void DrawPixelA(int* Colors, int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void DrawRectancle(int* Colors, int xMin, int xMax, int yMin, int yMax, unsigned char r, unsigned char g, unsigned char b);
	void DrawRectanclePrivate(int* Colors, int xMin, int xMax, int yMin, int yMax, unsigned char r, unsigned char g, unsigned char b);
	void DrawElips(int* Colors, int x0, int y0, int R, unsigned char r, unsigned char g, unsigned char b);
	void DrawLine(int* Colors, int x1, int x2, int y1, int y2, unsigned char r, unsigned char g, unsigned char b);
	void DrawLinePrivate(int* Colors, int x1, int x2, int y1, int y2, unsigned char r, unsigned char g, unsigned char b);
	void Write(int* Colors, int x1, int x2, int y1, int y2);
	void DrawElipsSmooth(int* Colors, int R, int x, int y, unsigned char r, unsigned char g, unsigned char b);
	void DrawTextFT(int* Colors, int fontSize, std::string text, int x, int y, unsigned char r, unsigned char g, unsigned char b);
	int GetWindowWidth();
	int GetWindowHeight();


	void setWindowWidth(int width);
	void setWindowHeight(int height);


private:
	int WinWidth;
	int WinHeight;
};