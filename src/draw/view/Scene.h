#pragma once
#include <memory>
#include <vector>

namespace draw {
	class Color;
	class Object;
	class Observer;
	class Point;
	class Polygon;
	class Shade;
	class ViewPort;
	class Scene {
	public:
		explicit Scene();
		void addObject(std::unique_ptr<Object>&&);
		void clearObjects();
		void draw() const;
		void update(const int, const int);
		const std::unique_ptr<Observer> observer;
		const std::unique_ptr<Shade> shade;
	private:
		std::unique_ptr<const ViewPort> wvp;
		std::vector<Point> frame;
		std::vector<std::unique_ptr<Object>> objects;
		std::vector<Polygon> renderPolygons;
		std::vector<std::vector<double>> zBuffers;
		std::vector<std::vector<Color>> cBuffers;
	};
}