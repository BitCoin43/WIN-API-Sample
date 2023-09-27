#pragma once
#include <ft2build.h>
#include <freetype/freetype.h>
#include FT_FREETYPE_H
#include <string>

class Text_rend {
public:
    class Point {
    public:
        Point(float x, float y) : x(x), y(y) {}
        float x;
        float y;
    };

public:
    class Edge {
        Edge(Point x, Point y) : x(x), y(y) {}
        Point x;
        Point y;
    };

    int orient(FT_Vector a, FT_Vector b, FT_Vector c) {
        double val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y);
        if (val == 0) return 0;
        return (val > 0) ? 1 : 2;
    }

    bool intersect(FT_Vector p1, FT_Vector q1, FT_Vector p2, FT_Vector q2) {
        int o1 = orient(p1, q1, p2);
        int o2 = orient(p1, q1, q2);
        int o3 = orient(p2, q2, p1);
        int o4 = orient(p2, q2, q1);

        if (o1 != o2 && o3 != o4) return true;
        return false;
    }

    void renderText(int* Colors, int width, int height, int fontSize, const char* text, int x, int y, unsigned char r, unsigned char g, unsigned char b);
    int getStringWidth(int size, std::string text);
};
