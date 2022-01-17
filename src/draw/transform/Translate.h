#pragma once
#include "Transform.h"

namespace draw {
	class Point;
	class Translate : public Transform {
	public:
		explicit Translate(const Point&);
		explicit Translate(const double, const double, const double);
		const double offsetX;
		const double offsetY;
		const double offsetZ;
	};
}
