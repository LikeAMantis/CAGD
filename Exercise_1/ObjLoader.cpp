#pragma once
#include "PointVector.hpp"
#include "ObjData.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class ObjLoader {
public:
    static bool parse(const std::string& path, ObjData& out) {
        std::ifstream file(path);

        if (!file.is_open()) {
            std::cerr << "Can't open file: " << path << '\n';
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                continue;
            }

            std::stringstream ss(line);
            std::string prefix;
            ss >> prefix;

            if (prefix == "v") {
                PointVector p;
                ss >> p.x;
                ss >> p.y;
                p.w = 1.f;

                out.vertices.push_back(p);
            } else if (prefix == "f") {
                int verticeIndex;
                while (ss >> verticeIndex) {
                    out.indeces.push_back(verticeIndex - 1);
                }
            }
        }

        return true;
    }
};
