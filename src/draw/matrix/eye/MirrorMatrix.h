#pragma once
#include "../Matrix.h"
#include "../../util/Axis.h"

namespace draw {
	class MirrorMatrix : public Matrix {
	public:
		explicit MirrorMatrix(const Axis);
		const Axis axis;
	};
}
