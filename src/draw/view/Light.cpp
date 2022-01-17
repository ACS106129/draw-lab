#include "Light.h"
#include "../Point.h"
#include "../color/Color.h"

namespace draw {
	Light::Light(const Light& copy) : Light(*copy.IPColor, *copy.IPos) {}

	Light::Light(const Color& c, const Point& p) : IPColor(new Color(c)), IPos(new Point(p.x, p.y, p.z, 0)) {}
}