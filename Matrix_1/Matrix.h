#pragma once
#include <string>
#include <iostream>

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

using namespace std;

string getLine(string text, size_t size, string gliph) {
	string out = text;
	for (int i = text.size(); i < size; i++) {
		out += gliph;
	}
	return out;
}

void printMatrix(Matrix A) {
	string line = "+";
	string sl = getLine("", 5, "-") + "+";
	for (int i = 0; i < A.getWidth(); i++) {
		line += sl;
	}
	cout << line << endl;
	for (int i = 0; i < A.getHeight(); i++) {
		cout << "|" << getLine(to_string(round(A.getElimentByIndex(0, 0))), 5, " ") << endl;
		cout << line << endl;
	}
}