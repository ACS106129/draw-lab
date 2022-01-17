#include "Rotate.h"
#include "../matrix/transform/TransformMatrix.h"

namespace draw {
	Rotate::Rotate(const Angle& x, const Angle& y, const Angle& z) :angleX(x), angleY(y), angleZ(z), Transform("Rotate") {
		transMatrix->transform(std::make_shared<const Rotate>(*this));
	}
}