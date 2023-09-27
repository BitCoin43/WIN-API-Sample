#pragma once
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

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
	Matrix(int width, int height, float value) : width(width), height(height) {
		float* a = new float[width * height];
		m = a;
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				m[x + width * y] = value;
			}
		}
		m = a;
	}
	Matrix(int width, int height, float* value) : width(width), height(height), m(value) {}
	Matrix(const Matrix& A) {
		width = A.width;
		height = A.height;
		m = new float[width * height];
		memcpy(m, A.m, width * height * sizeof(int));
	}
	~Matrix() {
		delete[] m;
	}
public:
	float getValue(int x, int y) {
		if (x < width && y < height) return m[x + y * width];
		else return FLT_MAX;
	}
	void setValue(int x, int y, float value) {
		m[x + y * width] = value;
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
	void setErr(int Error) {
		Err = Error;
	}
public:
	Matrix& operator*=(Matrix& A)
	{
		if (width == A.getHeight()) {
			Matrix R(A.getWidth(), height);

			for (int y = 0; y < height; y++) {
				for (int x = 0; x < A.getWidth(); x++) {
					float sum = 0;
					for (int k = 0; k < A.getWidth(); k++) {
						float a = m[k + y * width];
						float b = A.getValue(x, k);
						sum += a * b;
					}
					R.setValue(x, y, sum);
				}
			}
			float* r = new float[A.getWidth() * height];
			delete[] m;
			m = r;
			width = R.width;
			height = R.height;

			for (int x = 0; x < width; x++) {
				for (int y = 0; y < height; y++) {
					m[x + y * width] = R.getValue(x, y);
				}
			}

			return R;
		}
		else {
			Matrix R(1, 1);
			R.setValue(0, 0, FLT_MAX);
		}
	}
	Matrix& operator=(Matrix& A) {
		if (this != &A) {
			delete[] this->m;
			int size = A.getHeight() * A.getWidth();
			this->m = new float[size];
			memcpy(this->m, A.m, size * sizeof(int));
		}
		return *this;
	}
	Matrix& operator=(Matrix A) {
		if (this != &A) {
			delete[] this->m;
			int size = A.getHeight() * A.getWidth();
			this->m = new float[size];
			memcpy(this->m, A.m, size * sizeof(int));
		}
		return *this;
	}

private:
	float* m = nullptr;
	int width;
	int height;
	int Err = 0;
};

Matrix Err(1, 1, FLT_MAX);

Matrix operator*(Matrix A, Matrix B)
{
	if (A.getWidth() == B.getHeight()) {
		Matrix R(B.getWidth(), A.getHeight());

		for (int y = 0; y < A.getHeight(); y++) {
			for (int x = 0; x < B.getWidth(); x++) {
				float sum = 0;
				for (int k = 0; k < A.getWidth(); k++) {
					float a = A.getValue(k, y);
					float b = B.getValue(x, k);
					sum += a * b;
				}
				R.setValue(x, y, sum);
			}
		}
		return R;
	}
	else {
		return Err;
	}
}

Matrix operator+(Matrix& A, Matrix& B)
{
	if (A.getWidth() == B.getWidth() && A.getHeight() == B.getHeight()) {
		Matrix R(B.getWidth(), A.getHeight());

		for (int y = 0; y < A.getHeight(); y++) {
			for (int x = 0; x < B.getWidth(); x++) {				
				float sum = A.getValue(x, y) + B.getValue(x, y);
				R.setValue(x, y, sum);
			}
		}
		return R;
	}
	else {
		return Err;
	}
}

Matrix operator-(Matrix& A, Matrix& B)
{
	if (A.getWidth() == B.getWidth() && A.getHeight() == B.getHeight()) {
		Matrix R(B.getWidth(), A.getHeight());

		for (int y = 0; y < A.getHeight(); y++) {
			for (int x = 0; x < B.getWidth(); x++) {
				float sum = A.getValue(x, y) - B.getValue(x, y);
				R.setValue(x, y, sum);
			}
		}
		return R;
	}
	else {
		return Err;
	}
}

Matrix transpose(Matrix& A) {
	Matrix M(A.getHeight(), A.getWidth());
	for (int x = 0; x < A.getHeight(); x++) {
		for (int y = 0; y < A.getWidth(); y++) {
			M.setValue(x, y, A.getValue(y, x));
		}
	}
	return M;
}

Matrix diag(Matrix& A) {
	if (A.getWidth() == 1) {
		Matrix R(A.getHeight(), A.getHeight());
		for (int i = 0; i < A.getHeight(); i++) {
			R.setValue(i, i, A.getValue(0, i));
		}
		return R;
	}
	else {
		return Err;
	}
}

Matrix inverse(Matrix A) {
	int n = A.getWidth();
	Matrix B(n, 2 * n, 0.0f);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			B.setValue(i, j, A.getValue(i, j));
		}
		B.setValue(i, i + n, 1.0f);
	}
	for (int i = 0; i < n; i++) {
		if (B.getValue(i, i) == 0) {
			int nonzero_row = -1;
			for (int j = i + 1; j < n; j++) {
				if (B.getValue(j, i) != 0) {
					nonzero_row = j;
					break;
				}
			}
			if (nonzero_row != -1) {
				for (int k = i; k < 2 * n; k++) {
					float temp = B.getValue(i, k);
					B.setValue(i, k, B.getValue(nonzero_row, k));
					B.setValue(nonzero_row, k, temp);
				}
			}
		}
		float scale = B.getValue(i, i);
		if (scale != 0) {
			for (int j = i; j < 2 * n; j++) {
				B.setValue(i, j, B.getValue(i, j) / scale);
			}
		}
		for (int j = 0; j < n; j++) {
			if (j != i) {
				float factor = B.getValue(j, i);
				for (int k = i; k < 2 * n; k++) {
					B.setValue(j, k, B.getValue(j, k) - factor * B.getValue(i, k));
				}
			}
		}
	}
	Matrix inverse(n, n, 0.0f);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			inverse.setValue(i, j, B.getValue(i, j + n));
		}
	}
	return inverse;
}

float Norm(Matrix A, float exp) {
	if (A.getHeight() == 1) {
		float sum = 0;
		float v = 0;
		for (int i = 0; i < A.getWidth(); i++) {
			v = A.getValue(i, 0);
			sum += pow(v, exp);
		}
		float res = pow(sum, 1 / exp);
		return res;
	}
	else {
		return FLT_MAX;
	}
}

void normalizeVector(Matrix& A) {
	if (A.getWidth() != 1) { A.setErr(1); return; }
	float norm = Norm(A, 2);
	for (int i = 0; i < A.getHeight(); i++) {
		A.setValue(0, i, A.getValue(0, i) / norm);
	}
}

float det(Matrix matrix) {
	int size = matrix.getWidth();

	if (size == 1) {
		return matrix.getValue(0, 0);
	}

	if (size == 2) {
		float a = matrix.getValue(0, 0);
		float b = matrix.getValue(1, 1);
		float c = matrix.getValue(0, 1);
		float d = matrix.getValue(1, 0);
		return a * b - c * d;
	}

	float D = 0.0f;
	for (int i = 0; i < size; i++) {
		Matrix subMatrix(size - 1, size - 1);
		for (int j = 0; j < size - 1; j++) {
			for (int k = 0; k < size - 1; k++) {
				int row = j;
				int col = k;
				if (k >= i) {
					col = k + 1;
				}
				subMatrix.setValue(j, k, matrix.getValue(row + 1, col));
			}
		}

		float subDeterminant = det(subMatrix);

		float sign = (i % 2 == 0) ? 1.0f : -1.0f;
		D += sign * matrix.getValue(0, i) * subDeterminant;
	}

	return D;
}

float Tr(Matrix A) {
	int size = 0.0f;
	if (A.getHeight() >= A.getWidth()) size = A.getWidth();
	else size = A.getHeight();
	float sum = 0.0f;
	for (int i = 0; i < size; i++) sum += A.getValue(i, i);
	return sum;
}

string getLine(string text, size_t size, string gliph) {
	string out = text;
	for (int i = text.size(); i < size; i++) {
		out += gliph;
	}
	return out;
}

void printMatrix(Matrix A) {
	string line = "  +";
	string sl = getLine("", 5, "-") + "+";
	for (int i = 0; i < A.getWidth(); i++) {
		line += sl;
	}
	cout << line << endl;
	for (int i = 0; i < A.getHeight(); i++) {
		string sline = "  |";
		for (int j = 0; j < A.getWidth(); j++) {
			int a = round(A.getValue(j, i));
			if (a == -2147483648) {
				sline += getLine("Err", 5, " ") + "|";
			}
			else {
				sline += getLine(to_string(a), 5, " ") + "|";
			}
			
		}
		cout << sline << endl;
		cout << line << endl;
	}
	cout << "\n";
}
