#pragma once
#include "Shape.h"
#include "../Point.h"

namespace draw {
	class Triangle : public Shape {
	public:
		explicit Triangle(const std::vector<Point> & = { Point(-1, -1), Point(0, 1), Point(1, -1) },
			const Color = Color::YELLOW);
	};
}