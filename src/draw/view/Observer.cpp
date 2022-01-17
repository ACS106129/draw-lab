#include "Observer.h"
#include "../matrix/eye/EyeMatrix.h"
#include "../matrix/eye/GeneralRotationMatrix.h"
#include "../matrix/eye/MirrorMatrix.h"
#include "../matrix/eye/TiltMatrix.h"
#include "../matrix/transform/TransformMatrix.h"
#include "../matrix/projection/ProjectionMatrix.h"
#include "../view/ViewPort.h"

namespace draw {
	void Observer::setEye(const EyeMatrix& eye) {
		eyeMatrix = std::make_unique<const EyeMatrix>(eye);
		updateObserverMatrix();
	}

	void Observer::setProjection(const ProjectionMatrix& proj) {
		projectionMatrix = std::make_unique<ProjectionMatrix>(proj);
		updateObserverMatrix();
	}

	void Observer::setViewPort(const ViewPort& vp) {
		viewport = std::make_unique<const ViewPort>(vp);
		updateObserverMatrix();
	}

	const EyeMatrix& Observer::getEyeMatrix() const {
		return *eyeMatrix;
	}

	const Matrix& Observer::getMatrix() const {
		return *obMatrix;
	}

	const ProjectionMatrix& Observer::getProjectionMatrix() const {
		return *projectionMatrix;
	}

	const ViewPort& Observer::getViewport() const {
		return *viewport;
	}

	void Observer::updateObserverMatrix() {
		if (!eyeMatrix || !projectionMatrix || !viewport)
			return;
		projectionMatrix->setView(*viewport);
		obMatrix = std::make_unique<const Matrix>(*projectionMatrix * *eyeMatrix);
	}

	std::ostream& operator<<(std::ostream& out, const Observer& ob) {
		if (ob.eyeMatrix)
			out << "TE\n" << *ob.eyeMatrix->inversedTM << "\nGRM\n" << *ob.eyeMatrix->grM <<
			"\nMirror\n" << *ob.eyeMatrix->mirrorM << "\nTilt\n" << *ob.eyeMatrix->tiltM << "\nEM\n" << *ob.eyeMatrix;
		if (ob.projectionMatrix)
			out << "\nPM\n" << *ob.projectionMatrix;
		if (ob.obMatrix)
			return out << "\nOBM\n" << *ob.obMatrix;
		return out;
	}
}
