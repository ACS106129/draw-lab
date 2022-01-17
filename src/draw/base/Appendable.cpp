#include "Appendable.h"
#include "../Dot.h"

using namespace draw;

void Appendable::buffering(const int x, const int y) {
	if (!d)
		bufferingImpl(Dot(x, y));
}

void Appendable::buffering(const Dot& d) {
	buffering(d.x, d.y);
}

void Appendable::done() {
	if (d)
		return;
	d = doneFilter();
}

const bool Appendable::isDone() const {
	return d;
}

bool Appendable::doneFilter() {
	return true;
}
