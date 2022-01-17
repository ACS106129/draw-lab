#include "TiltMatrix.h"

namespace draw {
	TiltMatrix::TiltMatrix(const Angle& a) :angle(a) {
		const double s = std::sin(a.rad);
		const double c = std::cos(a.rad);
		matrix[0] = c;
		matrix[1] = s;
		matrix[4] = -s;
		matrix[5] = c;
	}
}
