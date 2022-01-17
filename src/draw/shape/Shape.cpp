#include <GL/glut.h>
#include <sstream>
#include "Shape.h"
#include "../Point.h"
#include "../view/ViewPort.h"

namespace draw {
	void Shape::setTransformMatrix(const TransformMatrix& tm) {
		matrix.reset(new TransformMatrix(tm));
		for (auto& v : vertices)
			v.transform(*matrix);
	}

	const std::vector<Point>& Shape::getVertices() const {
		return vertices;
	}

	void Shape::draw(const TransformMatrix& trMatrix, const ViewPort* const vp) const {
		std::vector<Point> buffers;
		std::transform(vertices.cbegin(), vertices.cend(), std::back_inserter(buffers), [&](const auto& v) { return v * trMatrix; });
		if (vp != nullptr)
			buffers = vp->getClippedVertices(buffers);
		if (buffers.empty())
			return;
		switch (color)
		{
		case Color::WHITE:
			glColor3f(1.f, 1.f, 1.f);
			break;
		case Color::YELLOW:
			glColor3f(1.f, 1.f, 0.f);
			break;
		default:
			throw new std::runtime_error("Color not existed");
		}
		glBegin(GL_LINE_STRIP);
		const auto size = buffers.size();
		for (size_t c = 0; c < size + 1;) {
			const auto& p = buffers[c++ % size];
			glVertex3d(p.x + 1, p.y + 1, p.z);
		}
		glEnd();
	}

	Shape::Shape(const ShapeType t, const Color c, const std::vector<Point>& vs) :
		type(t), color(c), vertices(vs), matrix(new TransformMatrix) {
		const int count = static_cast<int>(t);
		if (vs.size() != count) {
			std::stringstream ss;
			ss << t << " needs exactly " << count << " vertices";
			throw new std::runtime_error(ss.str());
		}
	}

	std::ostream& operator<<(std::ostream& out, const Shape& s) {
		out << s.type << "{";
		for (const auto& v : s.vertices)
			out << v << ", ";
		return out << "\b\b}";
	}
}