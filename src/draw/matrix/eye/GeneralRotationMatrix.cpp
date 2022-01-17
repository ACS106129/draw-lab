#include "GeneralRotationMatrix.h"
#include "../../Point.h"

namespace draw {
	GeneralRotationMatrix::GeneralRotationMatrix(const Point& z, const Axis ax) :
		top(new Point(ax == Axis::X ? 1.0 : 0, ax == Axis::Y ? 1.0 : 0, ax == Axis::Z ? 1.0 : 0)) {
		const auto v = top->crossProduct(z);
		const auto normV = v.normalize();
		const auto normZ = z.normalize();
		const auto normCrossZV = z.crossProduct(v).normalize();
		matrix[0] = normV.x;
		matrix[1] = normV.y;
		matrix[2] = normV.z;
		matrix[4] = normCrossZV.x;
		matrix[5] = normCrossZV.y;
		matrix[6] = normCrossZV.z;
		matrix[8] = normZ.x;
		matrix[9] = normZ.y;
		matrix[10] = normZ.z;
	}
}
