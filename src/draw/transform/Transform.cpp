#include "Transform.h"
#include "../matrix/transform/TransformMatrix.h"
#include "../util/Util.h"

namespace draw {
	const Transform Transform::operator*(const Transform& other) const {
		Transform copy(*this, true);
		copy.transMatrix->transform(std::shared_ptr<const Transform>(new Transform(other)));
		return copy;
	}

	Transform::Transform(const Transform& copy, const bool isCombined) :
		transMatrix(new TransformMatrix(*copy.transMatrix)), name(isCombined ? "Combined" : copy.name) {}

	Transform::Transform(const std::string& name) : transMatrix(new TransformMatrix), name(name) {}

	std::ostream& operator<<(std::ostream& out, const Transform& t) {
		const auto& matrix = t.transMatrix->get();
		out << t.name + " Function Matrix :[";
		for (size_t i = 0; i < matrix.size(); ++i) {
			if (i != 0 && i % 4 == 0)
				out << " ], [";
			out << stringFormat(" %.1f", matrix[i]);
		}
		return out << " ]";
	}
}