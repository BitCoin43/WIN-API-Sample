#include <iostream>

class float3 {
public:
	float3(float x, float y, float z) : x(x), y(y), z(z) {}
	float3() {}
	float z = 0.0f;
	float x = 0.0f;
	float y = 0.0f;
	
};

class Node {
public:
	Node(int poly, float3 sphere, float radius) 
		: 
		sphere(sphere), radius(radius), poly(poly) 
	{};
	Node(float3 sphere, float radius, Node* n, int count_of_child) 
		: 
		sphere(sphere), radius(radius), child(n), count_of_child(count_of_child) 
	{};
	Node() {};
	~Node() {
		delete child;
	};
	float3 sphere = {};
	float radius = 0;
	int count_of_child = 0;
	Node* child = nullptr;
	int poly = -1;
};

using namespace std;

int main()
{
	Node maine(-1, float3(0, 0, 0), 6.7f);
	Node* crone = new Node[3]{
		Node(1, float3(0, 0, 0), 6.7f),
		Node(7, float3(0, 0, 0), 6.7f),
		Node(3, float3(0, 0, 0), 6.7f)
	};
	Node* stick = new Node[2]{
		Node(-1, float3(0, 0, 0), 6.7f),
		Node(5, float3(0, 0, 0), 6.7f)
	};
	stick->child = crone;
	maine.child = stick;

	Node* f = (maine.child)->child;

	int d = (f + 1)->poly;
	int r = 0;



}