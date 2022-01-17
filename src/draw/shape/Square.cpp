#include "Square.h"
#include "../view/ViewPort.h"

namespace draw {
	Square::Square(const ViewPort& vp, const Color c) :
		Square({ Point(vp.left, vp.bottom), Point(vp.left, vp.top), Point(vp.right, vp.top), Point(vp.right, vp.bottom) }, c) {}

	Square::Square(const std::vector<Point>& vs, const Color c) : Shape(ShapeType::SQUARE, c, vs) {}
}