#pragma once
#include "Transform.h"
#include "../util/Angle.h"

namespace draw {
	class Rotate : public Transform {
	public:
		explicit Rotate(const Angle&, const Angle&, const Angle&);
		const Angle angleX;
		const Angle angleY;
		const Angle angleZ;
	};
}