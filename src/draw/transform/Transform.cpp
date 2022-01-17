#include "Transform.h"
#include "matrix/TransformMatrix.h"
#include "../util/Util.h"

namespace draw {
	const Transform Transform::operator*(const Transform& other) const {
		Transform copy(*this);
		copy.transMatrix->transform(&other);
		return copy;
	}

	Transform::Transform(const Transform& copy) : transMatrix(new TransformMatrix(*copy.transMatrix)), name("Combined") {}

	Transform::Transform(const std::string& name) : transMatrix(new TransformMatrix), name(name) {}

	std::ostream& operator<<(std::ostream& out, const Transform& t) {
		const auto& matrix = t.transMatrix->get();
		out << t.name + " Function Matrix :[";
		for (size_t i = 0; i < matrix.size(); ++i) {
			if (i != 0 && i % 3 == 0)
				out << " ], [";
			out << stringFormat(" %.1f", matrix[i]);
		}
		return out << " ]";
	}
}