#include <cmath>
#include "Angle.h"

namespace draw {
	const double Angle::PI = std::atan(1) * 4;

	const Angle Angle::degrees(const double deg) {
		return Angle(deg / 180 * PI);
	}

	const Angle Angle::radians(const double rad) {
		return Angle(rad);
	}

	Angle::Angle(const double rad) : deg(rad / PI * 180), rad(rad) {}
}