#pragma once
#include <ostream>

namespace draw {
	class Matrix;
	class ViewPort;
	class Point {
	public:
		explicit Point(const double = 0, const double = 0, const double = 0, const double = 1);
		void transform(const Matrix&);
		const double innerProduct(const Point&) const;
		const Point normalize() const;
		const Point perspective() const;
		const Point operator-() const;
		const Point crossProduct(const Point&) const;
		const Point operator-(const Point&) const;
		double x;
		double y;
		double z;
		double w;
	private:
		friend std::ostream& operator<< (std::ostream&, const Point&);
	};
}