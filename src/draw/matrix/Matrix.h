#pragma once
#include <ostream>
#include <vector>

namespace draw {
	class Point;
	class Matrix {
	public:
		static const Matrix IDENTITY;
		// copy constructor
		Matrix(const Matrix&);
		explicit Matrix(const std::vector<double> & = { 1.0, 0, 0, 0, 0, 1.0, 0, 0, 0, 0, 1.0, 0, 0, 0, 0, 1.0 });
		virtual ~Matrix() = default;
		virtual void reset();
		const std::vector<double>& get() const;
		const Point operator*(const Point&) const;
		const Matrix operator*(const Matrix& other) const;
	protected:
		std::vector<double> matrix;
	private:
		friend std::ostream& operator<< (std::ostream&, const Matrix&);
	};
}
