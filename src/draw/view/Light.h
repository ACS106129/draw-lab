#pragma once
#include <memory>

namespace draw {
	class Color;
	class Point;
	class Light {
	public:
		// copy constructor
		Light(const Light&);
		explicit Light(const Color&, const Point&);
		const std::unique_ptr<const Color> IPColor;
		const std::unique_ptr<const Point> IPos;
	};
}