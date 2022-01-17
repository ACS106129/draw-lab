#pragma once
#include <memory>
#include <ostream>

namespace draw {
	class EyeMatrix;
	class Matrix;
	class ProjectionMatrix;
	class ViewPort;
	class Observer {
	public:
		explicit Observer() = default;
		void setEye(const EyeMatrix&);
		void setProjection(const ProjectionMatrix&);
		void setViewPort(const ViewPort&);
		const EyeMatrix& getEyeMatrix() const;
		const Matrix& getMatrix() const;
		const ProjectionMatrix& getProjectionMatrix() const;
		const ViewPort& getViewport() const;
	private:
		void updateObserverMatrix();
		std::unique_ptr<const EyeMatrix> eyeMatrix;
		std::unique_ptr<const Matrix> obMatrix;
		std::unique_ptr<const ViewPort> viewport;
		std::unique_ptr<ProjectionMatrix> projectionMatrix;
		friend std::ostream& operator<< (std::ostream&, const Observer&);
	};
}