#include "TransformMatrix.h"
#include "../../transform/Rotate.h"
#include "../../transform/Scale.h"
#include "../../transform/Translate.h"

namespace draw {
	TransformMatrix::TransformMatrix(const TransformMatrix& copy) : Matrix(copy.matrix), transforms(copy.transforms) {}

	TransformMatrix::TransformMatrix(const std::shared_ptr<const Transform> tr) {
		if (tr == nullptr)
			return;
		if (const auto r = dynamic_cast<const Rotate*>(tr.get())) {
			const double sinX = std::sin(r->angleX.rad), cosX = std::cos(r->angleX.rad);
			const double sinY = std::sin(r->angleY.rad), cosY = std::cos(r->angleY.rad);
			const double sinZ = std::sin(r->angleZ.rad), cosZ = std::cos(r->angleZ.rad);
			matrix[0] = cosZ * cosY;
			matrix[1] = -sinZ * cosX + cosZ * sinY * sinX;
			matrix[2] = sinZ * sinX + cosZ * sinY * cosX;
			matrix[4] = sinZ * cosY;
			matrix[5] = cosZ * cosX + sinZ * sinY * sinX;
			matrix[6] = -cosZ * sinX + sinZ * sinY * cosX;
			matrix[8] = -sinY;
			matrix[9] = cosY * sinX;
			matrix[10] = cosY * cosX;
		}
		else if (const auto s = dynamic_cast<const Scale*>(tr.get())) {
			matrix[0] = s->extentX;
			matrix[5] = s->extentY;
			matrix[10] = s->extentZ;
		}
		else if (const auto t = dynamic_cast<const Translate*>(tr.get())) {
			matrix[3] = t->offsetX;
			matrix[7] = t->offsetY;
			matrix[11] = t->offsetZ;
		}
		else
			throw new std::runtime_error("Transform type not found!");
		transforms.emplace_back(tr);
	}

	void TransformMatrix::reset() {
		Matrix::reset();
		transforms.clear();
	}

	void TransformMatrix::transform(const std::shared_ptr<const Transform> tr) {
		const auto transM = TransformMatrix(tr);
		matrix = (transM * (*this)).get();
		transforms.push_back(transM.transforms[0]);
	}

	const std::vector<std::shared_ptr<const Transform>>& TransformMatrix::getTransforms() const {
		return transforms;
	}
}