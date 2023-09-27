#include "text_render.h"
#include <vector>
#include FT_OUTLINE_H 

void DrawPixel(int* Colors, int x, int y, unsigned char r, unsigned char g, unsigned char b, int width, int height)
{
	if (y < height && x < width && x >= 0 && y >= 0)
	{
		Colors[y * width + x] = (r << 16) | (g << 8) | b;
	}
}

void DrawLine(int* Colors, int x1, int x2, int y1, int y2, unsigned char r, unsigned char g, unsigned char b, int width)
{
	const int deltaX = abs(x2 - x1);
	const int deltaY = abs(y2 - y1);
	const int signX = x1 < x2 ? 1 : -1;
	const int signY = y1 < y2 ? 1 : -1;
	int error = deltaX - deltaY;
	DrawPixel(Colors, x2, y2, r, g, b, width, 720);
	while (x1 != x2 || y1 != y2)
	{
		DrawPixel(Colors, x1, y1, r, g, b, width, 720);
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

void DrawAlphaPixel(int* Colors, int width, int height, int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	if (x >= 0 && x < width && y >= 0 && y < height) {
		int color = Colors[y * width + x];

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

		Colors[y * width + x] = (r_r << 16) | (g_r << 8) | b_r;
	}
}

void Text_rend::renderText(int* Colors, int width, int height, int fontSize, const char* text, int x, int y,
	unsigned char r, unsigned char g, unsigned char b)
{
	FT_Library library;
	FT_Face face;
	FT_Init_FreeType(&library);
	FT_New_Face(library, "C:/code/First3DCleanCodeProject/arial.ttf", 0, &face);
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	int penX = x;
	int penY = y;

	for (size_t i = 0; i < strlen(text); i++) {
		FT_Load_Char(face, text[i], FT_LOAD_RENDER);
		FT_GlyphSlot slot = face->glyph;

		FT_Outline* outline = &slot->outline;
		FT_BBox box;
		FT_Outline_Get_CBox(outline, &box);

		int delta = fontSize * 0.75 - slot->bitmap.rows;
		for (int row = 0; row < slot->bitmap.rows; row++) {
			for (int col = 0; col < slot->bitmap.width; col++) {
				int alpha = slot->bitmap.buffer[row * slot->bitmap.width + col];
				DrawAlphaPixel(Colors, width, height, penX + col, penY + row + delta, r, g, b, alpha);
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

int Text_rend::getStringWidth(int size, std::string text)
{
	FT_Library library;
	FT_Face face;

	FT_Init_FreeType(&library);
	FT_New_Face(library, "C:/code/First3DCleanCodeProject/arial.ttf", 0, &face);
	//FT_Error er = FT_Set_Pixel_Sizes(face, 0, 0.01);
	FT_Set_Char_Size(face, 0, 64 * size, 0, 0);

	int scale = 0;

	int sum = 0;

	for (int t = 0; t < text.size(); t++) {
		FT_Error error = FT_Load_Char(face, text[t], FT_LOAD_NO_BITMAP);
		FT_GlyphSlot slot = face->glyph;
		FT_Outline* outline = &slot->outline;
		FT_BBox box;
		FT_Outline_Get_CBox(outline, &box);
		if (text[t] != ' ') {
			scale += box.xMax / 46;
		}
		else {
			scale += size;
		}
	}

	FT_Done_Face(face);
	FT_Done_FreeType(library);

	return scale;
}
