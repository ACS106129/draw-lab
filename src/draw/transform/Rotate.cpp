#include "Rotate.h"
#include "matrix/TransformMatrix.h"

namespace draw {
	Rotate::Rotate(const Angle& a) :angle(a), Transform("Rotate") {
		transMatrix->transform(this);
	}
}