#include "EyeMatrix.h"
#include "GeneralRotationMatrix.h"
#include "MirrorMatrix.h"
#include "TiltMatrix.h"
#include "../transform/TransformMatrix.h"
#include "../../Point.h"
#include "../../transform/Translate.h"
#include "../../util/Angle.h"

namespace draw {
	EyeMatrix::EyeMatrix(const EyeMatrix& copy) : EyeMatrix(*copy.eye, *copy.coi, copy.tiltM->angle) {}

	EyeMatrix::EyeMatrix(const Point& e, const Point& c, const Angle& a) : eye(new Point(e)), coi(new Point(c)),
		inversedTM(new TransformMatrix(std::make_shared<const Translate>(-e))), grM(new GeneralRotationMatrix(c - e, Axis::Y)),
		mirrorM(new MirrorMatrix(Axis::X)), tiltM(new TiltMatrix(a)) {
		matrix = (*tiltM * *mirrorM * *grM * *inversedTM).get();
	}
}
