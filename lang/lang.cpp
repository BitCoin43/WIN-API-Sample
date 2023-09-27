#include <iostream>
#include <string>

using namespace std;

enum class vartype {
    string = 1,
    number
};

class var {
public:
private:
    string value;
    vartype;
};

int main()
{
    std::cout << "Hello World!\n";
}
