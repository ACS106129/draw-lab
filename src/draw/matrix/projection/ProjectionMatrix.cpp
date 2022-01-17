#include "ProjectionMatrix.h"
#include "../../Point.h"
#include "../../util/Angle.h"
#include "../../view/ViewPort.h"

namespace draw {
	ProjectionMatrix::ProjectionMatrix(const ProjectionMatrix& copy) : ProjectionMatrix(copy.hither, copy.yon, copy.hav) {}

	ProjectionMatrix::ProjectionMatrix(const double hi, const double y, const Angle& h) : hither(hi), yon(y), hav(h) {
		const double tanRad = std::tan(hav.rad);
		const double z = yon / (yon - hither) * tanRad;
		matrix[10] = z;
		matrix[11] = -hither * z;
		matrix[14] = tanRad;
		matrix[15] = 0;
	}

	void ProjectionMatrix::setView(const ViewPort& vp) {
		matrix[5] = (vp.right - vp.left) / (vp.top - vp.bottom);
	}
}
