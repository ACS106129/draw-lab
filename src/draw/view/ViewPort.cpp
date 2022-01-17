#include "ViewPort.h"
#include "../Point.h"
#include "../util/Util.h"

namespace draw {
	ViewPort::ViewPort(const double l, const double r, const double b, const double t) : left(l), right(r), bottom(b), top(t) {}

	const ViewPort ViewPort::getWindowViewPort(const int w, const int h) const {
		return ViewPort((1 + left) * w / 2, (1 + right) * w / 2, (1 + bottom) * h / 2, (1 + top) * h / 2);
	}

	std::ostream& operator<<(std::ostream& out, const ViewPort& vp) {
		return out << stringFormat("[ %.2f %.2f %.2f %.2f ]", vp.left, vp.right, vp.bottom, vp.top);
	}
}
