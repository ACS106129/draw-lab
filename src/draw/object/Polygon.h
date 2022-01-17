#pragma once
#include <memory>
#include <vector>

namespace draw {
	enum class Axis;
	enum class RotationType;
	class Color;
	class Point;
	class Polygon {
	public:
		explicit Polygon(const std::vector<Point>&);
		const bool contains(const double, const double, const Point&) const;
		const std::tuple<int, int> getMinMax(const Axis) const;
		const Point getNormalVertex(const RotationType&) const;
		std::shared_ptr<const Color> shadingColor;
		std::vector<Point> vertices;
	};
}

