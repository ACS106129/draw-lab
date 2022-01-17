#include "Blueprint.h"
#include "../Point.h"
#include "../matrix/transform/TransformMatrix.h"
#include "../object/Polygon.h"

namespace draw {
	Blueprint::Blueprint(const size_t vSize, const size_t fSize) : vertices(vSize), faces(fSize) {}

	void Blueprint::addFace(const double x, const double y, const double z, const double w) {
		faces[fIndex++] = std::make_unique<Point>(x, y, z, w);
	}

	void Blueprint::addVertice(const double x, const double y, const double z) {
		vertices[vIndex++] = std::make_unique<Point>(x, y, z);
	}

	const std::vector<Polygon> Blueprint::buildPolygons(const TransformMatrix& tm) const {
		std::vector<Point> transVertices;
		std::vector<Polygon> polygons;
		for (const auto& v : vertices)
			transVertices.emplace_back(tm * *v);
		for (const auto& f : faces) {
			std::vector<Point> poly{ transVertices[(int)f->x - 1], transVertices[(int)f->y - 1], transVertices[(int)f->z - 1] };
			if (f->w >= 1)
				poly.emplace_back(transVertices[(int)f->w - 1]);
			polygons.emplace_back(poly);
		}
		return polygons;
	}

	std::ostream& operator<<(std::ostream& out, const Blueprint& obj) {
		const auto vSize = obj.vertices.size();
		const auto fSize = obj.faces.size();
		for (size_t i = 0; i < vSize; ++i)
			out << "Vertex(" << i + 1 << "): " << *obj.vertices[i] << '\n';
		for (size_t i = 0; i < fSize; ++i) {
			const auto j = i + 1;
			out << "Face(" << j << "): " << *obj.faces[i] << (j != fSize ? '\n' : '\0');
		}
		return out;
	}
}