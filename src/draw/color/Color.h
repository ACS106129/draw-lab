#pragma once

namespace draw {
	class Color {
	public:
		static const Color BLACK;
		static const Color BLUE;
		static const Color GREEN;
		static const Color RED;
		static const Color WHITE;
		explicit Color(const double, const double, const double);
		const Color operator*(const double) const;
		const Color operator+(const Color&) const;
		const Color operator*(const Color&) const;
		double r;
		double g;
		double b;
	};
}
