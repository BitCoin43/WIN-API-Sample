#include <iostream>

int foo1(int x) {
	return x * x;
}

int foo2(int x) {
	return x + 1;
}

void g(int(*f)(int)) {
	for (int i = 0; i < 10; i++) {
		std::cout << f(i) << std::endl;
	}
}

int main() {
	g(foo1);
	g(foo2);
}