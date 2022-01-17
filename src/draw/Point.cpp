#include "Point.h"
#include "matrix/Matrix.h"
#include "util/Axis.h"
#include "util/Util.h"

namespace draw {
	Point::Point(const double x, const double y, const double z, const double w) : x(x), y(y), z(z), w(w) {}

	void Point::transform(const Matrix& trMatrix) {
		const Point p = trMatrix * (*this);
		x = p.x;
		y = p.y;
		z = p.z;
		w = p.w;
	}

	const double Point::getValue(const Axis axis) const {
		switch (axis) {
		case Axis::X:
			return x;
		case Axis::Y:
			return y;
		case Axis::Z:
			return z;
		case Axis::W:
			return w;
		default:
			throw new std::runtime_error("Axis is not existed!");
		}
	}

	const double Point::innerProduct(const Point& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	const Point Point::normalize() const {
		const double norm = std::sqrt(innerProduct(*this));
		if (norm == 0)
			return Point();
		return Point(x / norm, y / norm, z / norm, w);
	}

	const Point Point::perspective() const {
		if (w == 1)
			return *this;
		return Point(x / w, y / w, z / w);
	}

	const Point Point::operator-() const {
		return Point(-x, -y, -z, w);
	}

	const Point Point::crossProduct(const Point& other) const {
		return Point(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x, w);
	}

	const Point Point::operator-(const Point& other) const {
		return Point(x - other.x, y - other.y, z - other.z, w);
	}

	const Point Point::operator+(const Point& other) const {
		return Point(x + other.x, y + other.y, z + other.z, w);
	}

	const Point Point::operator*(const double scalar) const {
		return Point(x * scalar, y * scalar, z * scalar, w);
	}

	std::ostream& operator<<(std::ostream& out, const Point& p) {
		return out << stringFormat("[ %f, %f, %f ]", p.x, p.y, p.z);
	}
}