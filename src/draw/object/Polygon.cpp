#include <algorithm>
#include "Polygon.h"
#include "../Point.h"
#include "../color/Color.h"
#include "../util/Axis.h"
#include "../util/RotationType.h"

namespace draw {
	Polygon::Polygon(const std::vector<Point>& p) : vertices(p) {}

	const bool Polygon::contains(const double x, const double y, const Point& norm) const {
		const size_t size = vertices.size();
		for (size_t i = 0; i < size; ++i) {
			const auto& v = vertices[i];
			if ((vertices[(i + 1) % size] - v).crossProduct(Point(x, y, 0, 0) - v).z * norm.z < 0)
				return false;
		}
		return true;
	}

	const std::tuple<int, int> Polygon::getMinMax(const Axis axis) const {
		const auto [minVal, maxVal] = std::minmax_element(vertices.cbegin(), vertices.cend(),
			[=](const Point a, const Point b) { return a.getValue(axis) < b.getValue(axis);	});
		return { static_cast<int>(std::trunc(minVal->getValue(axis))), static_cast<int>(std::ceil(maxVal->getValue(axis))) };
	}

	const Point Polygon::getNormalVertex(const RotationType& type) const {
		return (vertices[1] - vertices[0]).crossProduct(vertices[2] - vertices[1]) * (type == RotationType::CLOCKWISE ? -1 : 1);
	}
}
