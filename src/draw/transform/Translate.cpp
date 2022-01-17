#include "Translate.h"
#include "matrix/TransformMatrix.h"

namespace draw {
	Translate::Translate(const double x, const double y) :offsetX(x), offsetY(y), Transform("Translate") {
		transMatrix->transform(this);
	}
}