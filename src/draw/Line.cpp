#include "Line.h"
#include "Dot.h"

using namespace draw;

Line::Line(const Line& l) : Line(*l.dots.front(), *l.dots.front()) {}
Line::Line(const Line& l, const Color c) : Line(*l.dots.front(), *l.dots.front(), c) {}
Line::Line(const Dot& d, const Color c) : Line(d, d, c) {}
Line::Line(const Dot& d1, const Dot& d2, const Color c) : Drawable(c) {
	dots.emplace_back(new Dot(d1, c));
	dots.emplace_back(new Dot(d2, c));
}

void Line::append() {
	done();
}

bool Line::doneFilter() {
	bufferingImpl(*dots.back());
	dots.shrink_to_fit();
	return true;
}

void Line::bufferingImpl(const Dot& d) {
	const Dot offset(d - *dots.front());
	// overlap needs to be counted as 1
	const Dot absOffset(std::max(std::abs(offset.x), 1), std::max(std::abs(offset.y), 1));
	const int base = absOffset.max();
	const float increX = static_cast<float>(offset.x) / base;
	const float increY = static_cast<float>(offset.y) / base;
	// start and end point
	const int size = base + 1;
	dots.resize(size);
	for (int i = 1; i < size; ++i)
		dots[i].reset(new Dot(dots.front()->x + static_cast<int>(std::round(increX * i)),
			dots.front()->y + static_cast<int>(std::round(increY * i)), color));
}
void Line::draw() const {
	for (auto& d : dots)
		d->draw();
}

void Line::print(std::ostream& o) const {
	if (isDone())
		o << "Line endpoint: (" << dots.front()->x << ", " << dots.back()->y << ")";
	else
		o << "Line startpoint: (" << dots.front()->x << ", " << dots.back()->y << ")";
}

const Dot& Line::getEndDot() const {
	return *dots.back();
}

const Dot& Line::getStartDot() const {
	return *dots.front();
}
