#include "Color.h"

namespace draw {
	const Color Color::BLACK(0, 0, 0);
	const Color Color::BLUE(0, 0, 1);
	const Color Color::GREEN(0, 1, 0);
	const Color Color::RED(1, 0, 0);
	const Color Color::WHITE(1, 1, 1);

	Color::Color(const double r, const double g, const double b) : r(r), g(g), b(b) {}

	const Color Color::operator*(const Color& other) const {
		return Color(r * other.r, g * other.g, b * other.b);
	}

	const Color Color::operator+(const Color& other) const {
		return Color(r + other.r, g + other.g, b + other.b);
	}

	const Color Color::operator*(const double scalar) const {
		return Color(r * scalar, g * scalar, b * scalar);
	}
}
