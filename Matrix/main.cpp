#include "Matrix.h"

int main()
{   
	float* v = new float[4] {
		1, 2, 
		2, 4
	};
	Matrix A(1, 19, 5);


	Matrix Y(1, 19, 2);

	printMatrix(inverse(transpose(A) * A) * transpose(A) * Y);


}

