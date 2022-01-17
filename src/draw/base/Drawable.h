#pragma once
#include <memory>
namespace draw {
	enum class Color {
		RED,
		BLUE,
		GREED,
		YELLOW
	};
	class Drawable {
	public:
		virtual void draw() const = 0;
		const Color color;
		virtual ~Drawable() = default;
	protected:
		explicit Drawable(Color);
	};
	class Dot;
	class Line;
	class Circle;
	class Polygon;
	typedef std::unique_ptr<draw::Drawable> upDraw;
	typedef std::unique_ptr<draw::Dot> upDot;
	typedef std::unique_ptr<draw::Line> upLine;
	typedef std::unique_ptr<draw::Circle> upCircle;
	typedef std::unique_ptr<draw::Polygon> upPolygon;
	typedef std::unique_ptr<const draw::Drawable> upcDraw;
	typedef std::unique_ptr<const draw::Dot> upcDot;
	typedef std::unique_ptr<const draw::Line> upcLine;
	typedef std::unique_ptr<const draw::Circle> upctCircle;
	typedef std::unique_ptr<const draw::Polygon> upcPolygon;
}