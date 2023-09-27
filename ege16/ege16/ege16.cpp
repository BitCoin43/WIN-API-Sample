#include <iostream>

int main()
{
    float count = 0;
    float s = 0;
    int min = 10000;
    int max = 0;
    for (int i = 4855; i < 7857; i++) {
        if (i % 6 == 0 && i % 15 == 0 && i % 7 != 0 && i % 16 != 0) {
            count++;
            s += i;
            if (i < min) min = i;
            if (i > max) max = i;
        }
    }
    float y = s / count;
    std::cout << "sr: " << y << std::endl;
    std::cout << "min: " << min << std::endl;
    std::cout << "max: " << max << std::endl;
    std::cout << "out: " << max + min + y << std::endl;
}

