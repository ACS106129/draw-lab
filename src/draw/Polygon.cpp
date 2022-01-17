#include <algorithm>
#include "Dot.h"
#include "Line.h"
#include "Polygon.h"

using namespace draw;

Polygon::Polygon(const Dot& d, const Color c) : Drawable(c) {
	lines.emplace_back(new Line(d, c));
}

void Polygon::append() {
	lines.back()->done();
	lines.emplace_back(new Line(lines.back()->getEndDot(), lines.front()->getStartDot(), color));
}

void Polygon::bufferingImpl(const Dot& d) {
	lines.back()->buffering(d);
}

bool Polygon::doneFilter() {
	if (lines.size() < 2)
		return false;
	append();
	lines.back()->done();
	return true;
}

void Polygon::draw() const {
	for (auto& l : lines)
		l->draw();
}

void Polygon::print(std::ostream& o) const {
	const auto& d = lines.back()->getStartDot();
	o << "Polygon vertex (" << lines.size() << "): (" << d.x << ", " << d.y << ")";
}

const std::vector<Dot> Polygon::getDots() const {
	std::vector<Dot> dots;
	std::transform(lines.begin(), lines.end(), std::back_inserter(dots), [](auto& l) { return l->getStartDot(); });
	return dots;
}
