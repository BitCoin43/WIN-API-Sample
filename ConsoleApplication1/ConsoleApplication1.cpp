#include <iostream>

using namespace std;

int main() {
	for (int i = 1; i < 180; i++) {
		float a = 180 - i;
		a = a / 2;
		cout << i << ": " << a << endl;
	}
}