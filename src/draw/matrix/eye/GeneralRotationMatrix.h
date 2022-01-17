#pragma once
#include "../Matrix.h"
#include "../../util/Axis.h"

namespace draw {
	class GeneralRotationMatrix : public Matrix {
	public:
		explicit GeneralRotationMatrix(const Point&, const Axis);
		const std::unique_ptr<const Point> top;
	};
}
