#pragma once
#include "PointVector.hpp"
#include <vector>

struct ObjData {
    std::vector<PointVector> vertices;
    std::vector<int> indeces;

    friend std::ostream& operator<<(std::ostream& os, const ObjData& v) {
        for (auto& vertex : v.vertices) {
            os << "vertex: " << vertex << '\n';
        }
        os << "indeces: ";
        for (auto& index : v.indeces) {
            os << index << " ";
        }
        os << '\n';
        return os;
    }
};
