#pragma once
#include <memory>
#include "ViewPort.h"

namespace draw {
	class Point;
	class Shape;
	class TransformMatrix;
	class View {
	public:
		explicit View(const ViewPort& window, const ViewPort& viewpoint);
		void draw() const;
		void clear();
		void add(const std::shared_ptr<Shape>&);
		const std::vector<Point>& getVertices() const;
		const ViewPort windowViewPort;
		const ViewPort viewpointViewPort;
		virtual ~View() = default;
	private:
		std::vector<std::shared_ptr<Shape>> children;
		std::unique_ptr<const TransformMatrix> matrix;
		friend std::ostream& operator<< (std::ostream&, const View&);
	};
}