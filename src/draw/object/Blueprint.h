#pragma once
#include <memory>
#include <ostream>
#include <vector>

namespace draw {
	class Object;
	class Point;
	class TransformMatrix;
	class Blueprint {
	public:
		explicit Blueprint(const size_t, const size_t);
		void addFace(const double, const double, const double, const double = 0);
		void addVertice(const double, const double, const double);
		const std::vector<std::vector<Point>> buildPolygons(const TransformMatrix&) const;
	private:
		int fIndex = 0;
		int vIndex = 0;
		std::vector<std::unique_ptr<Point>> faces;
		std::vector<std::unique_ptr<Point>> vertices;
		friend std::ostream& operator<< (std::ostream&, const Blueprint&);
	};
}
