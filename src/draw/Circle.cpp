#include <cassert>
#include "Circle.h"
#include "Dot.h"
#include "Line.h"

using namespace draw;

Circle::Circle(const Dot& d, const Color c) : Drawable(c), radius(new Line(d, d, c)) {}

void Circle::append() {
	radius->done();
	done();
}

void Circle::bufferingImpl(const Dot& d) {
	radius->buffering(d);
	const auto r = static_cast<int>(std::round(getRadius()));
	const int range = static_cast<int>(std::round(getRadius() / std::sqrt(2)));
	auto& anchor = radius->getStartDot();
	dots.resize(4 + range * 8);
	dots[0].reset(new Dot(anchor.x, anchor.y + r, color));
	dots[1].reset(new Dot(anchor.x, anchor.y - r, color));
	dots[2].reset(new Dot(anchor.x + r, anchor.y, color));
	dots[3].reset(new Dot(anchor.x - r, anchor.y, color));
	for (int i = 1; i <= range; ++i) {
		bool assign = false;
		for (int j = r; j >= 0; --j) {
			if (static_cast<int>(std::round(Dot(i, j).distance())) != r)
				continue;
			dots[3 + i].reset(new Dot(anchor.x + i, anchor.y + j, color));
			dots[3 + i + range].reset(new Dot(anchor.x - i, anchor.y + j, color));
			dots[3 + i + range * 2].reset(new Dot(anchor.x + i, anchor.y - j, color));
			dots[3 + i + range * 3].reset(new Dot(anchor.x - i, anchor.y - j, color));
			dots[3 + i + range * 4].reset(new Dot(anchor.x + j, anchor.y + i, color));
			dots[3 + i + range * 5].reset(new Dot(anchor.x - j, anchor.y + i, color));
			dots[3 + i + range * 6].reset(new Dot(anchor.x + j, anchor.y - i, color));
			dots[3 + i + range * 7].reset(new Dot(anchor.x - j, anchor.y - i, color));
			assign = true;
			break;
		}
		assert(assign);
	}

}

void Circle::draw() const {
	if (!isDone())
		radius->draw();
	for (auto& d : dots)
		d->draw();
}

void Circle::print(std::ostream& o) const {
	if (isDone())
		o << "Circle radius: " << getRadius();
	else
		o << "Circle center: (" << radius->getStartDot().x << "," << radius->getStartDot().y << ")";
}

const Dot& Circle::getCircleCenter() const {
	return radius->getStartDot();
}

const float Circle::getRadius() const {
	return radius->getEndDot().distance(radius->getStartDot());
}
