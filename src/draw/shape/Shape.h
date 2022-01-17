#pragma once
#include "ShapeType.h"
#include "../color/Color.h"
#include "../transform/matrix/TransformMatrix.h"

namespace draw {
	class Point;
	class Transform;
	class ViewPort;
	class Shape {
	public:
		void setTransformMatrix(const TransformMatrix&);
		const std::vector<Point>& getVertices() const;
		virtual void draw(const TransformMatrix & = TransformMatrix(), const ViewPort* const = nullptr) const;
		virtual ~Shape() = default;
	protected:
		explicit Shape(const ShapeType, const Color, const std::vector<Point>&);
		std::unique_ptr<TransformMatrix> matrix;
		std::vector<Point> vertices;
	private:
		const Color color;
		const ShapeType type;
		friend std::ostream& operator<< (std::ostream&, const Shape&);
	};
}
