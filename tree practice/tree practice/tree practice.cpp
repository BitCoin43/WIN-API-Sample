#include <iostream>

using namespace std;

class node {
public:
    node(int g) : x(g) {}
    node* n = nullptr;
    int x;
    void p() { std::cout << x << std::endl; }
};


int main()
{
    node* f = { new node[3]{node(1), node(2), node(7)} };
    node m(5);
    m.n = f;
    cout << m.n[3].x;
}


