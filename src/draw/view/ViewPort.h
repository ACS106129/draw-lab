#pragma once
#include <ostream>
#include <vector>

namespace draw {
	class Point;
	class ViewPort {
	public:
		explicit ViewPort(const double = 0.0, const double = 0.0, const double = 0.0, const double = 0.0);
		const std::vector<Point> getClippedVertices(const std::vector<Point>&) const;
		const double left;
		const double right;
		const double bottom;
		const double top;
		virtual ~ViewPort() = default;
	private:
		const size_t getClipType(const double, const double, const double, const double) const;
		const std::vector<Point> getClippedVerticesImpl(const bool, const Point&, const Point&) const;
		friend std::ostream& operator<< (std::ostream&, const ViewPort&);
	};
}

