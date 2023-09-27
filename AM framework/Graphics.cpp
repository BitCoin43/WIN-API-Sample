#include "Graphics.h"
#include <iostream>
#include <assert.h>
#include FT_OUTLINE_H 

Graphics::Graphics(int WindowWidth, int WindowHeight)
	:
	WinWidth(WindowWidth),
	WinHeight(WindowHeight)
{
}

Graphics::~Graphics()
{
}

void Graphics::FillScreenFast(int* Colors, unsigned char r, unsigned char g, unsigned char b)
{
	for (int* i = Colors, *end = &Colors[WinWidth * WinHeight]; i < end; i++)
	{
		*i = (r << 16) | (g << 8) | b;
	}
}

void Graphics::ClearScreenSuperFast(int* Colors)
{
	std::memset(Colors, 0, WinWidth * WinHeight * 4);
}

void Graphics::DrawPixel(int* Colors, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	if (x >= 0 && x < WinWidth && y > 25 && y < WinHeight)
	{
		Colors[y * WinWidth + x] = (r << 16) | (g << 8) | b;
	}
}

void Graphics::DrawPixelPrivate(int* Colors, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	if (x >= 0 && x < WinWidth && y >= 0 && y < WinHeight)
	{
		Colors[y * WinWidth + x] = (r << 16) | (g << 8) | b;
	}
}

void Graphics::DrawPixelA(int* Colors, int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	if (x >= 0 && x < WinWidth && y >= 0 && y < WinHeight) {
		int color = Colors[y * WinWidth + x];

		float r_b = ((color >> 16) & 0x000000ff) / 255.0;
		float g_b = ((color >> 8) & 0x000000ff) / 255.0;
		float b_b = (color & 0x000000ff) / 255.0;

		float r_u = r / 255.0;
		float g_u = g / 255.0;
		float b_u = b / 255.0;

		float al = a / 255.0;

		unsigned char r_r = (r_u * al + r_b * (1 - al)) * 255;
		unsigned char g_r = (g_u * al + g_b * (1 - al)) * 255;
		unsigned char b_r = (b_u * al + b_b * (1 - al)) * 255;

		Colors[y * WinWidth + x] = (r_r << 16) | (g_r << 8) | b_r;
	}
}

void Graphics::DrawRectancle(int* Colors, int xMin, int xMax, int yMin, int yMax, unsigned char r, unsigned char g, unsigned char b)
{
	for (int y = yMin; y < yMax; y++)
	{
		for (int x = xMin; x < xMax; x++)
		{
			DrawPixel(Colors, x, y, r, g, b);
		}
	}
}

void Graphics::DrawRectanclePrivate(int* Colors, int xMin, int xMax, int yMin, int yMax, unsigned char r, unsigned char g, unsigned char b)
{
	for (int y = yMin; y < yMax; y++)
	{
		for (int x = xMin; x < xMax; x++)
		{
			DrawPixelPrivate(Colors, x, y, r, g, b);
		}
	}
}

void Graphics::DrawElips(int* Colors, int x0, int y0, int R, unsigned char r, unsigned char g, unsigned char b)
{
	int x = 0;
	int y = R;
	int delta = 1 - 2 * R;
	int error = 0;
	bool wt = true;
	int q1 = x0;
	int q2 = x0;
	while (y >= 0)
	{
		DrawPixel(Colors, x0 + x, y0 + y, r, g, b);
		if (wt)
		{
			q1 = x0 + x;
			wt = false;
		}
		else
		{
			q2 = x0 + x;
			wt = false;
		}

		if (q2 - q1 != 1)
		{

		}


		if (true)
		{
			int x1 = 0;
			while (x1 < R + 1)
			{
				if ((x0 - x + x1) < x0)
				{
					DrawPixel(Colors, x0 + x - x1, y0 + y, r, g, b);
				}
				x1++;
			}
		}

		DrawPixel(Colors, x0 + x, y0 - y, r, g, b);
		if (true)
		{
			int y1 = 0;
			while (y1 < R)
			{
				if ((y0 - y + y1) < y0 + 1)
				{
					DrawPixel(Colors, x0 + x, y0 - y + y1, r, g, b);
					y1++;
				}
				else
				{
					break;
				}
			}
		}

		DrawPixel(Colors, x0 - x, y0 + y, r, g, b);
		if (true)
		{
			int y1 = 0;
			while (y1 < R)
			{
				if ((y0 - y + y1) < y0 + 1)
				{
					DrawPixel(Colors, x0 - x, y0 + y - y1, r, g, b);
					y1++;
				}
				else
				{
					break;
				}
			}
		}
		DrawPixel(Colors, x0 - x, y0 - y, r, g, b);
		if (true)
		{
			int x1 = 0;
			while (x1 < R + 1)
			{
				if ((x0 - x + x1) < x0 + 1)
				{
					DrawPixel(Colors, x0 - x + x1, y0 - y, r, g, b);
				}
				x1++;
			}
		}
		DrawPixel(Colors, x0, y0, r, g, b);
		error = 2 * (delta + y) * 2 - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) * 2 - 1;
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}

void Graphics::DrawLine(int* Colors, int x1, int x2, int y1, int y2, unsigned char r, unsigned char g, unsigned char b)
{
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	DrawPixel(Colors, x2, y2, r, g, b);
	while (x1 != x2 || y1 != y2)
	{
		DrawPixel(Colors, x1, y1, r, g, b);
		int error2 = error * 2;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}

void Graphics::DrawLinePrivate(int* Colors, int x1, int x2, int y1, int y2, unsigned char r, unsigned char g, unsigned char b)
{
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	DrawPixelPrivate(Colors, x2, y2, r, g, b);
	while (x1 != x2 || y1 != y2)
	{
		DrawPixelPrivate(Colors, x1, y1, r, g, b);
		int error2 = error * 2;
		if (error2 > -deltaY)
		{
			error -= deltaY;
			x1 += signX;
		}
		if (error2 < deltaX)
		{
			error += deltaX;
			y1 += signY;
		}
	}
}

void Graphics::Write(int* Colors, int x1, int x2, int y1, int y2)
{
	int r = 100;
	for (int i = -r; i < r; i++) {
		for (int j = -r; j < r; j++) {
			if (i * i + j * j < r * r) {
				DrawPixel(Colors, i + 100, j + 100, 0, 0, 255);
			}
		}
	}
}

void Graphics::DrawElipsSmooth(int* Colors, int R, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	for (int xi = -R; xi < R; xi++) {
		for (int yi = -R; yi < R; yi++) {
			unsigned char c = 0;
			for (int cx = 0; cx < 16; cx++) {
				for (int cy = 0; cy < 16; cy++) {
					int lx = xi * 16 + cx;
					int ly = yi * 16 + cy;
					int lr = R * 16;
					int s = lx * lx + ly * ly;
					int rr = lr * lr;
					if (s < rr) {
						if (c == 255) c--;
						c++;
					}
				}
			}
			unsigned char t = c;
			DrawPixelA(Colors, x + xi, y + yi, r, g, b, t);
		}
	}
}

void Graphics::DrawTextFT(int* Colors, int fontSize, std::string text, int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
	FT_Library library;
	FT_Face face;
	FT_Init_FreeType(&library);
	FT_New_Face(library, "C:/code/First3DCleanCodeProject/arial.ttf", 0, &face);
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	int penX = x;
	int penY = y;

	for (size_t i = 0; i < text.size(); i++) {
		FT_Load_Char(face, text[i], FT_LOAD_RENDER);
		FT_GlyphSlot slot = face->glyph;

		FT_Outline* outline = &slot->outline;
		FT_BBox box;
		FT_Outline_Get_CBox(outline, &box);

		int delta = fontSize * 0.75 - slot->bitmap.rows;
		for (int row = 0; row < slot->bitmap.rows; row++) {
			for (int col = 0; col < slot->bitmap.width; col++) {
				int alpha = slot->bitmap.buffer[row * slot->bitmap.width + col];
				DrawPixelA(Colors, penX + col, penY + row + delta, r, g, b, alpha);
			}
		}
		penX += slot->bitmap.width;
		if (text[i] == ' ') {
			penX += fontSize * 0.2f;
		}
	}
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

int Graphics::GetWindowWidth()
{
	return WinWidth;
}

int Graphics::GetWindowHeight()
{
	return WinHeight;
}

void Graphics::setWindowWidth(int width)
{
	WinWidth = width;
}

void Graphics::setWindowHeight(int height)
{
	WinHeight = height;
}
