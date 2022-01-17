#pragma once
#include "Shape.h"
#include "../Point.h"

namespace draw {
	class ViewPort;
	class Square : public Shape {
	public:
		explicit Square(const std::vector<Point> & = { Point(-1, -1), Point(-1, 1), Point(1, 1), Point(1, -1) },
			const Color = Color::YELLOW);
		explicit Square(const ViewPort&, const Color = Color::YELLOW);
	};
}

