#pragma once
#include "../Matrix.h"
#include "../../util/Axis.h"

namespace draw {
	class Angle;
	class GeneralRotationMatrix;
	class MirrorMatrix;
	class TiltMatrix;
	class TransformMatrix;
	class EyeMatrix : public Matrix {
	public:
		// copy constructor
		EyeMatrix(const EyeMatrix&);
		explicit EyeMatrix(const Point&, const Point&, const Angle&);
		const std::unique_ptr<const Point> eye;
		const std::unique_ptr<const Point> coi;
		const std::unique_ptr<const TransformMatrix> inversedTM;
		const std::unique_ptr<const GeneralRotationMatrix> grM;
		const std::unique_ptr<const MirrorMatrix> mirrorM;
		const std::unique_ptr<const TiltMatrix> tiltM;
	};
}
