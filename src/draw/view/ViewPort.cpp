#include "ViewPort.h"
#include "../Point.h"
#include "../util/Util.h"

namespace draw {
	ViewPort::ViewPort(const double l, const double r, const double b, const double t) :
		left(l), right(r), bottom(b), top(t) {}

	const std::vector<Point> ViewPort::getClippedVertices(const std::vector<Point>& vertices) const {
		std::vector<Point> origins = vertices;
		std::vector<Point> results;
		for (size_t i = 0; i < 2; ++i) {
			results.clear();
			const auto size = origins.size();
			for (size_t j = 0; j < size; ++j)
				for (const auto& v : getClippedVerticesImpl(i == 0, origins[j], origins[(j + 1) % size]))
					if (results.empty() || results.back() != v)
						results.emplace_back(v);
			origins = results;
		}
		return results;
	}

	const size_t ViewPort::getClipType(const double start, const double end, const double minBound, const double maxBound) const {
		// four bits abcd
		// min bound matches a(start), b(end) => outside 1, inside 0
		// max bound matches c(start), d(end) => outside 1, inside 0
		size_t type = 0;
		if (minBound - start > 0)
			type |= 8;
		if (minBound - end > 0)
			type |= 4;
		if (maxBound - start < 0)
			type |= 2;
		if (maxBound - end < 0)
			type |= 1;
		return type;
	}

	const std::vector<Point> ViewPort::getClippedVerticesImpl(const bool isMajorAxisX,
		const Point& startVertex, const Point& endVertex) const {
		const auto offset = endVertex - startVertex;
		const double sDenoOrigin = isMajorAxisX ? startVertex.x : startVertex.y;
		const double eDenoOrigin = isMajorAxisX ? endVertex.x : endVertex.y;
		const double minBound = isMajorAxisX ? left : bottom;
		const double maxBound = isMajorAxisX ? right : top;
		const size_t clipType = getClipType(sDenoOrigin, eDenoOrigin, minBound, maxBound);
		double slope = 0.0;
		// both inside two bounds
		if (clipType == 0)
			return { endVertex };
		// both vertices outside any of bounds | divided by zero
		else if (clipType == 0b1100 || clipType == 0b0011 || !(isMajorAxisX ? offset.slopeX(slope) : offset.slopeY(slope)))
			return {};
		Point s = startVertex;
		Point e = endVertex;
		// either start or end inside any of bounds
		double& sNume = isMajorAxisX ? s.y : s.x;
		double& sDeno = isMajorAxisX ? s.x : s.y;
		double& eNume = isMajorAxisX ? e.y : e.x;
		double& eDeno = isMajorAxisX ? e.x : e.y;
		// start outside min bound
		if (clipType & 0b1000)
			sDeno = minBound;
		// start outside max bound
		else if (clipType & 0b0010)
			sDeno = maxBound;
		if (sDeno != sDenoOrigin)
			sNume += slope * (sDeno - sDenoOrigin);
		// end outside min bound
		if (clipType & 0b0100)
			eDeno = minBound;
		// end outside max bound
		else if (clipType & 0b0001)
			eDeno = maxBound;
		if (eDeno != eDenoOrigin)
			eNume = sNume + slope * (eDeno - sDeno);
		if (s == startVertex)
			return { e };
		return { s, e };
	}

	std::ostream& operator<<(std::ostream& out, const ViewPort& vp) {
		return out << stringFormat("[ %.2f %.2f %.2f %.2f ]", vp.left, vp.right, vp.bottom, vp.top);
	}
}
