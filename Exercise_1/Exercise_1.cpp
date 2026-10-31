// Exercise_1.cpp : Defines the entry point for the application.
//

#include "Exercise_1.h"
#include <stdexcept>

using namespace std;

struct PointVector {
	float x;
	float y;
	float w{ 1.f };

	static PointVector add(const PointVector& lhs, const PointVector& rhs) {
		if (lhs.w + rhs.w > 1.f) {
			cout << "Point with Point addition is not allowed" << "\n";
		}

		return PointVector{
			lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.w + rhs.w
		};
	}

	static PointVector subtract(const PointVector& lhs, const PointVector& rhs) {
		if (lhs.w - rhs.w != 0.f) {
			cout << "Point with Vector subtraction is not allowed" << "\n";
		}

		return PointVector{
			lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.w - rhs.w
		};
	}

	static PointVector scalarMult(float lhs, const PointVector& rhs) {
		if (rhs.w == 1.f) {
			cout << "Scalar with Point Multiplikation is not allowed" << "\n";
		}

		return PointVector{
			lhs * rhs.x,
			lhs * rhs.y,
			rhs.w
		};
	}

	static float dot(const PointVector& lhs, const PointVector& rhs) {
		if (lhs.w != 0.f || rhs.w != 0.f) {
			cout << "Only Vector with Vector Dot Product is allowed" << "\n";
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

int main()
{
	PointVector p1{ 1, 2 };
	PointVector p2{ 2, 3 };
	PointVector v1{ 3, 4, 0.f };
	PointVector v2{ 5, 2, 0.f };

	cout << p1 + p2 << "\n";
	cout << p1 - p2 << "\n";
	cout << v1 - v2 << "\n";
	cout << v1 - p2 << "\n";
	cout << p1 * p2 << "\n";
	cout << v1 * v2 << "\n";
	cout << 2.f * v1 << "\n";

	return 0;
}
