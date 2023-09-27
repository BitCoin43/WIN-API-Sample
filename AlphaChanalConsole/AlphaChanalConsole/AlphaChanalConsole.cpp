#include <iostream>

using namespace std;

int setColor(unsigned char r, unsigned char g, unsigned char b) {
    return (r << 16) | (g << 8) | b;
}

inline unsigned char get_r(int color) {
    return color >> 16;
}

inline unsigned char get_g(int color) {
    return color << 16 >> 24;
}

inline unsigned char get_b(int color) {
    return color << 24 >> 24;
}

int blend(int color, int up, unsigned char a) {
    float r_b = get_r(color) / 255.0;
    float g_b = get_g(color) / 255.0;
    float b_b = get_b(color) / 255.0;

    float r_u = get_r(up) / 255.0;
    float g_u = get_g(up) / 255.0;
    float b_u = get_b(up) / 255.0;

    float al = a / 255.0;

    unsigned char r = (r_u * al + r_b * (1 - al)) * 255;
    unsigned char g = (g_u * al + g_b * (1 - al)) * 255;
    unsigned char b = (b_u * al + b_b * (1 - al)) * 255;

    return setColor(r, g, b);
}

void cal(int color) {
    int r = get_r(color);
    int g = get_g(color);
    int b = get_b(color);
    cout << "R=" << r << " G=" << g << " B=" << b << endl << endl;
}

int main()
{
    int first =  setColor(170, 
                          231, 
                          98);
    int second = setColor(255, 
                          255, 
                          0);

    cout << "first:" << endl;
    cal(first);
    cout << "second:" << endl;
    cal(second);
    cout << "after blend:" << endl;
    int f = blend(first, second, 1);
    cal(f);
    
    
}

