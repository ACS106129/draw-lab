#include "Translate.h"
#include "../Point.h"
#include "../matrix/transform/TransformMatrix.h"

namespace draw {
	Translate::Translate(const Point& p) : Translate(p.x, p.y, p.z) {}

	Translate::Translate(const double x, const double y, const double z) : offsetX(x), offsetY(y), offsetZ(z), Transform("Translate") {
		transMatrix->transform(std::make_shared<const Translate>(*this));
	}
}