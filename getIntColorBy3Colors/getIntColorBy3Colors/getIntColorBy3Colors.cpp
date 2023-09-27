#include <iostream>

int getColor(unsigned char r, unsigned char g, unsigned char b) {
    return (r << 16) | (g << 8) | b;
}

int main()
{
    std::cout << getColor(80, 59, 137) << std::endl;
}

