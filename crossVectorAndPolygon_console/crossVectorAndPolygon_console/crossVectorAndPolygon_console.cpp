#include <iostream>

using namespace std;

class vector {
public:
    vector(float x, float y, float z) : x(x), y(y), z(z) {}
    float x;
    float y;
    float z;
    void print() {
        cout << "x: " << x << ",  y: " << y << ",  z: " << z << endl;
    }
};

vector min(vector v1, vector v2) {
    return vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vector add(vector v1, vector v2) {
    return vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

vector mul(vector v1, float t) {
    return vector(v1.x * t, v1.y * t, v1.z * t);
}

vector one(vector v) {
    return vector(1 - v.x, 1 - v.y, 1 - v.z);
}

vector cross(const vector& v1, const vector& v2)
{

    return vector(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x);

}

float dot(vector v1, vector v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float squar(float a, float b, float c) {
    float p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

class polygon {
public:
    polygon(vector vec1, vector vec2, vector vec3) : point1(vec1), point2(vec2), point3(vec3) {}
    vector point1;
    vector point2;
    vector point3;
};

vector cross(vector origin, vector direction, polygon poly) {
    vector E1 = min(poly.point2, poly.point1);
    vector E2 = min(poly.point3, poly.point1);
    vector T = min(origin, poly.point1);
    vector P = cross(direction, E2);
    vector Q = cross(T, E1);
    float t = (1 / dot(P, E1)) * dot(Q, E2);
    float u = (1 / dot(P, E1)) * dot(P, T);
    float v = (1 / dot(P, E1)) * dot(Q, direction);
    vector r = add(mul(poly.point2, (1 - u - v)), add(mul(poly.point3, u), mul(poly.point1, v)));
    return r;
}

bool in_t(vector p, polygon poly) {
    int inside = 0;
    float AB = sqrt((poly.point1.x - poly.point2.x) * (poly.point1.x - poly.point2.x) + (poly.point1.y - poly.point2.y) * (poly.point1.y - poly.point2.y) + (poly.point1.z - poly.point2.z) * (poly.point1.z - poly.point2.z));
    float BC = sqrt((poly.point2.x - poly.point3.x) * (poly.point2.x - poly.point3.x) + (poly.point2.y - poly.point3.y) * (poly.point2.y - poly.point3.y) + (poly.point2.z - poly.point3.z) * (poly.point2.z - poly.point3.z));
    float CA = sqrt((poly.point1.x - poly.point3.x) * (poly.point1.x - poly.point3.x) + (poly.point1.y - poly.point3.y) * (poly.point1.y - poly.point3.y) + (poly.point1.z - poly.point3.z) * (poly.point1.z - poly.point3.z));

    float AP = sqrt((p.x - poly.point1.x) * (p.x - poly.point1.x) + (p.y - poly.point1.y) * (p.y - poly.point1.y) + (p.z - poly.point1.z) * (p.z - poly.point1.z));
    float BP = sqrt((p.x - poly.point2.x) * (p.x - poly.point2.x) + (p.y - poly.point2.y) * (p.y - poly.point2.y) + (p.z - poly.point2.z) * (p.z - poly.point2.z));
    float CP = sqrt((p.x - poly.point3.x) * (p.x - poly.point3.x) + (p.y - poly.point3.y) * (p.y - poly.point3.y) + (p.z - poly.point3.z) * (p.z - poly.point3.z));
    float diff = (squar(AP, BP, AB) + squar(AP, CP, CA) + squar(BP, CP, BC)) - squar(AB, BC, CA);
    if (fabs(diff) < 1) inside = 1;
    return inside;

}

int main()
{
    vector p[3] = { vector(1, 0, 0), vector(0, 1, 0), vector(0, 0, 1) };

    polygon poly(p[0], p[1], p[2]);

    vector vec = cross(vector(0, 0, 0), vector(1, 1, 1), poly);
    vec.print();
    cout << in_t(vec, poly);
}
