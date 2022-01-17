#pragma once
#include <ostream>

namespace draw {
	class TransformMatrix;
	class ViewPort;
	class Point {
	public:
		explicit Point(const double = 0, const double = 0, const double = 1);
		void transform(const TransformMatrix&);
		const bool slopeX(double&) const;
		const bool slopeY(double&) const;
		const bool operator==(const Point&) const;
		const bool operator!=(const Point&) const;
		const Point operator-(const Point&) const;
		const Point operator*(const TransformMatrix&) const;
		double x;
		double y;
		double z;
	private:
		friend std::ostream& operator<< (std::ostream&, const Point&);
	};
}