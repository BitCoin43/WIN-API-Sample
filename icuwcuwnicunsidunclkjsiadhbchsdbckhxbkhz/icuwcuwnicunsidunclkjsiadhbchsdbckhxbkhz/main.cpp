#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

std::thread g() {
	std::thread t ([] {for (int y = 0; y < 100; y++) cout << y << endl; });
	return t;
}

int main() {
	std::cout << "hello world!" << std::endl;
	
	//std::thread d([] {for (int i = 0; i < 100; i++) std::cout << i << std::endl; });
	//d.detach();
	//std::thread t([]{for (int i = 0; i < 100; i++) std::cout << "new thread"<< std::endl; });
	//t.join();
	thread t = g();
	t.join();
	std::chrono::seconds duration(2);
	std::this_thread::sleep_for(duration);
}
