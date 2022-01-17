#include "Point.h"
#include "transform/matrix/TransformMatrix.h"
#include "util/Util.h"
#include "view/ViewPort.h"

namespace draw {
	Point::Point(const double x, const double y, const double z) : x(x), y(y), z(z) {}

	void Point::transform(const TransformMatrix& trMatrix) {
		const Point p = operator*(trMatrix);
		x = p.x;
		y = p.y;
		z = p.z;
	}

	const bool Point::slopeX(double& s) const {
		if (x == 0)
			return false;
		s = y / x;
		return true;
	}

	const bool Point::slopeY(double& s) const {
		if (y == 0)
			return false;
		s = x / y;
		return true;
	}

	const bool Point::operator==(const Point& other) const {
		return x == other.x && y == other.y && z == other.z;
	}

	const bool Point::operator!=(const Point& other) const {
		return !(*this == other);
	}

	const Point Point::operator-(const Point& other) const {
		return Point(x - other.x, y - other.y, z);
	}

	const Point Point::operator*(const TransformMatrix& trMatrix) const {
		const auto& m = trMatrix.get();
		return Point(m[0] * x + m[1] * y + m[2] * z, m[3] * x + m[4] * y + m[5] * z, m[6] * x + m[7] * y + m[8] * z);
	}

	std::ostream& operator<<(std::ostream& out, const Point& p) {
		return out << stringFormat("[ %f, %f, %f ]", p.x, p.y, p.z);
	}
}