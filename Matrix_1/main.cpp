#include <iostream>
#include <string>

class Matrix {
public:
	Matrix(int width, int height) : width(width), height(height) {
		float* a = new float[width * height];
		m = a;
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				if (x == y) m[x + width * y] = 1.0f;
				else m[x + width * y] = 0.0f;
			}
		}
		m = a;
	}
	~Matrix() {
		delete[] m;
	}
	float getElimentByIndex(int x, int y) {
		if (x < width && y < height) return m[y * width + x];
		else return FLT_MAX;
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
private:
	float* m;
	int width;
	int height;
};

int main() {
	Matrix A(3, 3);
	std::string text = "hgg";
	std::cout << text;

	return 0;
}