#include "View.h"
#include "../Point.h"
#include "../shape/Square.h"
#include "../transform/matrix/TransformMatrix.h"

namespace draw {
	View::View(const ViewPort& w, const ViewPort& v) : windowViewPort(w), viewpointViewPort(v) {
		const double unitX = (v.right - v.left) / (w.right - w.left);
		const double unitY = (v.top - v.bottom) / (w.top - w.bottom);
		const double distX = v.left - (unitX * w.left);
		const double distY = v.bottom - (unitY * w.bottom);
		matrix.reset(new TransformMatrix({ unitX, 0, distX, 0, unitY, distY, 0, 0, 1 }));
		children.emplace_back(new Square(viewpointViewPort, Color::WHITE));
	}

	void View::draw() const {
		auto iter = children.cbegin();
		(*iter++)->draw();
		while (iter != children.cend())
			(*iter++)->draw(*matrix, &viewpointViewPort);
	}

	void View::clear() {
		children.clear();
	}

	void View::add(const std::shared_ptr<Shape>& s) {
		children.emplace_back(s);
	}

	const std::vector<Point>& View::getVertices() const {
		return (*children.cbegin())->getVertices();
	}

	std::ostream& operator<<(std::ostream& out, const View& v) {
		return out << *v.matrix;
	}
}