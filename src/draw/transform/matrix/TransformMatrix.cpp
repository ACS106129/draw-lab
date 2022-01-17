#include <sstream>
#include "TransformMatrix.h"
#include "../Rotate.h"
#include "../Scale.h"
#include "../Translate.h"
#include "../../util/Util.h"

namespace draw {
	TransformMatrix::TransformMatrix(const Transform* const tr) : TransformMatrix() {
		if (const auto r = dynamic_cast<const Rotate*>(tr)) {
			const double s = std::sin(r->angle.rad), c = std::cos(r->angle.rad);
			matrix[0] = c;
			matrix[1] = -s;
			matrix[3] = s;
			matrix[4] = c;
		}
		else if (const auto s = dynamic_cast<const Scale*>(tr)) {
			matrix[0] = s->horizontal;
			matrix[4] = s->vertical;
		}
		else if (const auto t = dynamic_cast<const Translate*>(tr)) {
			matrix[2] = t->offsetX;
			matrix[5] = t->offsetY;
		}
	}

	TransformMatrix::TransformMatrix(const std::vector<double>& m) {
		if (m.size() != 9)
			throw new std::runtime_error("Transform matrix size must be 9!");
		matrix = m;
	}

	void TransformMatrix::transform(const Transform* const tr) {
		matrix = (TransformMatrix(tr) * (*this)).matrix;
	}

	void TransformMatrix::reset() {
		matrix = { 1.0, 0, 0, 0, 1.0, 0, 0, 0, 1.0 };
	}

	const std::vector<double>& TransformMatrix::get() const {
		return matrix;
	}

	const TransformMatrix TransformMatrix::operator*(const TransformMatrix& other) const {
		std::vector<double> result(9);
		for (size_t i = 0; i < result.size(); ++i) {
			const size_t row = (i / 3) * 3, col = i % 3;
			double temp = 0.0;
			for (size_t j = 0; j < 3; ++j)
				temp += matrix[row + j] * other.matrix[col + j * 3];
			result[i] = temp;
		}
		return TransformMatrix(result);
	}

	std::ostream& operator<<(std::ostream& out, const TransformMatrix& trMatrix) {
		std::stringstream ss;
		out << "[";
		for (size_t i = 0; i < trMatrix.matrix.size(); ++i) {
			if (i != 0 && i % 3 == 0)
				out << " ]\n[";
			std::string fmt;
			if (std::abs(trMatrix.matrix[i]) < 0.1 && trMatrix.matrix[i] != 0) {
				ss << " " << std::scientific << trMatrix.matrix[i];
				fmt = ss.str();
				ss.str(std::string());
			}
			else
				fmt = stringFormat(" %f", trMatrix.matrix[i]);
			fmt = fmt.substr(0, fmt.find_last_not_of('0') + 1);
			if (fmt[fmt.size() - 1] == '.')
				fmt = fmt.substr(0, fmt.size() - 1);
			out << fmt;
		};
		return out << " ]";
	}
}
