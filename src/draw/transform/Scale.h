#pragma once
#include "Transform.h"

namespace draw {
	class Scale : public Transform {
	public:
		explicit Scale(const double, const double, const double);
		const double extentX;
		const double extentY;
		const double extentZ;
	};
}