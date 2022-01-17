#include "Scale.h"
#include "matrix/TransformMatrix.h"

namespace draw {
	Scale::Scale(const double h, const double v) :horizontal(h), vertical(v), Transform("Scale") {
		transMatrix->transform(this);
	}
}