#pragma once
#include "Transform.h"

namespace draw {
	class Translate : public Transform {
	public:
		explicit Translate(const double, const double);
		const double offsetX;
		const double offsetY;
	};
}
