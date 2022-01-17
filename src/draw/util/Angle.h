#pragma once

namespace draw {
	class Angle {
	public:
		static const Angle degrees(const double);
		static const Angle radians(const double);
		static const double PI;
		const double deg;
		const double rad;
	protected:
		explicit Angle(const double);
	};
}