#include "Scale.h"
#include "../matrix/transform/TransformMatrix.h"

namespace draw {
	Scale::Scale(const double x, const double y, const double z) :extentX(x), extentY(y), extentZ(z), Transform("Scale") {
		transMatrix->transform(std::make_shared<Scale>(*this));
	}
}