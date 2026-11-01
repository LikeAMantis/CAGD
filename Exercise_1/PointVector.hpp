#pragma once
#include <iostream>

struct PointVector {
    float x;
    float y;
    float w{ 1.f };

    static PointVector makePoint(float x, float y) {
        return PointVector{ x, y, 1.f };
    }

    static PointVector makeVector(float x, float y) {
        return PointVector{ x, y, 0.f };
    }

    static PointVector add(const PointVector& lhs, const PointVector& rhs) {
        if (lhs.w + rhs.w > 1.f) {
            std::cerr << "Point with Point addition is not allowed" << "\n";
        }

        return PointVector{
            lhs.x + rhs.x,
            lhs.y + rhs.y,
            lhs.w + rhs.w
        };
    }

    static PointVector subtract(const PointVector& lhs, const PointVector& rhs) {
        if (lhs.w - rhs.w != 0.f) {
            std::cerr << "Point with Vector subtraction is not allowed" << "\n";
        }

        return PointVector{
            lhs.x - rhs.x,
            lhs.y - rhs.y,
            lhs.w - rhs.w
        };
    }

    static PointVector scalarMult(float lhs, const PointVector& rhs) {
        if (rhs.w == 1.f) {
            std::cerr << "Scalar with Point Multiplikation is not allowed" << "\n";
        }

        return PointVector{
            lhs * rhs.x,
            lhs * rhs.y,
            rhs.w
        };
    }

    static float dot(const PointVector& lhs, const PointVector& rhs) {
        if (lhs.w != 0.f || rhs.w != 0.f) {
            std::cerr << "Only Vector with Vector Dot Product is allowed" << "\n";
        }

        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    friend PointVector operator+(PointVector lhs, const PointVector& rhs) {
        return PointVector::add(lhs, rhs);
    }

    friend PointVector operator-(PointVector lhs, const PointVector& rhs) {
        return PointVector::subtract(lhs, rhs);
    }

    friend PointVector operator*(const float& lhs, const PointVector& rhs) {
        return PointVector::scalarMult(lhs, rhs);
    }

    friend float operator*(PointVector lhs, const PointVector& rhs) {
        return PointVector::dot(lhs, rhs);
    }

    friend std::ostream& operator<<(std::ostream& os, const PointVector& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.w << ")";
        return os;
    }
};
