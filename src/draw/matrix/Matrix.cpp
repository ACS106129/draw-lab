#include <sstream>
#include "Matrix.h"
#include "../Point.h"
#include "../util/Util.h"

namespace draw {
	const Matrix Matrix::IDENTITY;

	Matrix::Matrix(const Matrix& copy) : Matrix(copy.matrix) {}

	Matrix::Matrix(const std::vector<double>& m) {
		if (m.size() != 16)
			throw new std::runtime_error("Matrix size must be 16!");
		matrix = m;
	}

	void Matrix::reset() {
		matrix = IDENTITY.matrix;
	}

	const std::vector<double>& Matrix::get() const {
		return matrix;
	}

	const Point Matrix::operator*(const Point& p) const {
		const auto& m = matrix;
		return Point(
			m[0] * p.x + m[1] * p.y + m[2] * p.z + m[3] * p.w,
			m[4] * p.x + m[5] * p.y + m[6] * p.z + m[7] * p.w,
			m[8] * p.x + m[9] * p.y + m[10] * p.z + m[11] * p.w,
			m[12] * p.x + m[13] * p.y + m[14] * p.z + m[15] * p.w);
	}

	const Matrix Matrix::operator*(const Matrix& other) const {
		std::vector<double> result(16);
		for (size_t i = 0; i < result.size(); ++i) {
			const size_t row = (i / 4) * 4, col = i % 4;
			double temp = 0.0;
			for (size_t j = 0; j < 4; ++j)
				temp += matrix[row + j] * other.matrix[col + j * 4];
			result[i] = temp;
		}
		return Matrix(result);
	}

	std::ostream& operator<<(std::ostream& out, const Matrix& trMatrix) {
		std::stringstream ss;
		out << "[";
		for (size_t i = 0; i < trMatrix.matrix.size(); ++i) {
			if (i != 0 && i % 4 == 0)
				out << " ]\n[";
			std::string fmt;
			if (std::abs(trMatrix.matrix[i]) < 0.01 && trMatrix.matrix[i] != 0) {
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
