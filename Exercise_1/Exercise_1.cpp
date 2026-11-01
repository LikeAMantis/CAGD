#include "ObjLoader.cpp"
#include "PointVector.hpp"
#include <cstdlib>
#include <iostream>
#include <malloc.h>

using namespace std;
int main() {
    // Ex 1.1
    // PointVector p1{ 1, 2 };
    // PointVector p2{ 2, 3 };
    // PointVector v1{ 3, 4, 0.f };
    // PointVector v2{ 5, 2, 0.f };
    // PointVector v2{ 5, 2, 0.f };

    // cout << p1 + p2 << "\n";
    // cout << p1 - p2 << "\n";
    // cout << v1 - v2 << "\n";
    // cout << v1 - p2 << "\n";
    // cout << p1 * p2 << "\n";
    // cout << v1 * v2 << "\n";
    // cout << 2.f * v1 << "\n";

    // Ex 1.2.1
    ObjData objData;
    string path{ ASSET_DIR "/Curve_1.obj" };

    if (ObjLoader::parse(path, objData)) {
        std::cout << "objData from path: " << path << "\n"
                  << objData << '\n';
    }
}