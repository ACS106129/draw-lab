#pragma once
#include <functional>
#include <memory>
#include <vector>

namespace draw {
	class Light;
	class Observer;
	class Point;
	class Polygon;
	class Shade;
	class Object {
	public:
		explicit Object(const Light&, const std::vector<Polygon>&);
		void clipping(const int, const int, const Observer&);
		void draw() const;
		void reset();
		void shading(const Observer&, const Shade&);
		const std::vector<Polygon>& getRenderPolygons() const;
		const std::unique_ptr<const Light> light;
		const std::vector<Polygon> polygons;
	private:
		static const std::vector<std::function<double(const Point&)>> clipFuncs;
		std::vector<Polygon> renderPolygons;
		friend std::ostream& operator<< (std::ostream&, const Object&);
	};
}
