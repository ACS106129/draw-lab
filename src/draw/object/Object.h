#pragma once
#include <functional>
#include <memory>
#include <vector>

namespace draw {
	class Observer;
	class Point;
	class Object {
	public:
		explicit Object() = default;
		void draw() const;
		void reset();
		void addPolygons(const std::vector<std::vector<Point>>&);
		void setView(const int, const int, const Observer&, const bool);
	private:
		static const std::vector<std::function<double(const Point&)>> clipFuncs;
		std::vector<Point> frame;
		std::vector<std::vector<Point>> polygons;
		std::vector<std::vector<Point>> clippedPolygons;
		friend std::ostream& operator<< (std::ostream&, const Object&);
	};
}
