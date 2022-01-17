#pragma once
#include "../Matrix.h"
#include "../../util/Angle.h"

namespace draw {
	class ViewPort;
	class ProjectionMatrix : public Matrix {
	public:
		// copy constructor
		ProjectionMatrix(const ProjectionMatrix&);
		explicit ProjectionMatrix(const double, const double, const Angle&);
		void setView(const ViewPort&);
		const double hither;
		const double yon;
		const Angle hav;
	};
}
