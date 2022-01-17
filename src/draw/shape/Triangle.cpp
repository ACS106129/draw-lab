#include "Triangle.h"

namespace draw {
	Triangle::Triangle(const std::vector<Point>& vs, const Color c) : Shape(ShapeType::TRIANGLE, c, vs) {}
}