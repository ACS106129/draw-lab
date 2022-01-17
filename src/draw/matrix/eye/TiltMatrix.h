#pragma once
#include "../Matrix.h"
#include "../../util/Angle.h"

namespace draw {
	class TiltMatrix : public Matrix {
	public:
		explicit TiltMatrix(const Angle&);
		const Angle angle;
	};
}
