#pragma once
#include <ostream>
#include <vector>

namespace draw {
	class Transform;
	class TransformMatrix {
	public:
		explicit TransformMatrix(const Transform* const);
		explicit TransformMatrix(const std::vector<double> & = { 1.0, 0, 0, 0, 1.0, 0, 0, 0, 1.0 });
		void transform(const Transform* const);
		void reset();
		const std::vector<double>& get() const;
		// same as matrix multiply
		const TransformMatrix operator*(const TransformMatrix& other) const;
		virtual ~TransformMatrix() = default;
	private:
		std::vector<double> matrix;
		friend std::ostream& operator<< (std::ostream&, const TransformMatrix&);
	};
}

