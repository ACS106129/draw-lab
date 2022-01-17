#include "MirrorMatrix.h"

namespace draw {
	MirrorMatrix::MirrorMatrix(const Axis a) : axis(a) {
		switch (axis) {
		case Axis::X:
			matrix[0] = -1.0;
			break;
		case Axis::Y:
			matrix[5] = -1.0;
			break;
		case Axis::Z:
			matrix[10] = -1.0;
			break;
		default:
			break;
		}
	}
}
