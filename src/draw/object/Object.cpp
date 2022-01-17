#include <algorithm>
#include <execution>
#include <GL/glut.h>
#include "Object.h"
#include "../Point.h"
#include "../matrix/projection/ProjectionMatrix.h"
#include "../matrix/transform/TransformMatrix.h"
#include "../transform/Scale.h"
#include "../transform/Translate.h"
#include "../view/Observer.h"
#include "../view/Viewport.h"

namespace draw {
	const std::vector<std::function<double(const Point&)>> Object::clipFuncs = {
		[](const auto& v) { return v.w - v.x; },
		[](const auto& v) { return v.w + v.x; },
		[](const auto& v) { return v.w - v.y; },
		[](const auto& v) { return v.w + v.y; },
		[](const auto& v) { return v.w - v.z; },
		[](const auto& v) { return v.z; }
	};

	void Object::draw() const {
		if (clippedPolygons.empty())
			return;
		glBegin(GL_LINE_STRIP);
		glColor3f(1.f, 1.f, 1.f);
		const auto size = frame.size();
		for (size_t c = 0; c < size + 1;) {
			const auto& p = frame[c++ % size];
			glVertex4d(p.x + 1, p.y + 1, p.z + 1, p.w);
		}
		glEnd();
		glColor3f(1.f, 1.f, 0.f);
		for (const auto& pg : clippedPolygons) {
			const auto size = pg.size();
			glBegin(GL_LINE_STRIP);
			for (size_t c = 0; c < size + 1;) {
				const auto& p = pg[c++ % size];
				glVertex4d(p.x + 1, p.y + 1, p.z + 1, p.w);
			}
			glEnd();
		}
	}

	void Object::reset() {
		polygons.clear();
		clippedPolygons.clear();
		frame.clear();
	}

	void Object::addPolygons(const std::vector<std::vector<Point>>& pgs) {
		polygons.insert(polygons.cend(), pgs.cbegin(), pgs.cend());
	}

	void Object::setView(const int w, const int h, const Observer& ob, const bool isNoBackfaces) {
		clippedPolygons.clear();
		const auto& obM = ob.getMatrix();
		std::vector<Point> buffers, clipCheckpoint;
		for (const auto& polygon : polygons) {
			const auto size = polygon.size();
			buffers.resize(size);
			// projection to buffers
			for (size_t i = 0; i < size; ++i)
				buffers[i] = obM * polygon[i];
			for (const auto& func : clipFuncs) {
				clipCheckpoint.clear();
				const auto bufSize = buffers.size();
				for (size_t i = 0; i < bufSize; ++i) {
					const auto& startVertex = buffers[i];
					const auto& endVertex = buffers[(i + 1) % bufSize];
					const double clippedSV = func(startVertex);
					const double clippedEV = func(endVertex);
					// both inside
					if (clippedSV >= 0 && clippedEV >= 0) {
						clipCheckpoint.emplace_back(endVertex);
						continue;
					}
					const double scaler = clippedSV / (clippedSV - clippedEV);
					const Point newV{ startVertex.x + (endVertex.x - startVertex.x) * scaler,
						startVertex.y + (endVertex.y - startVertex.y) * scaler,
						startVertex.z + (endVertex.z - startVertex.z) * scaler,
						startVertex.w + (endVertex.w - startVertex.w) * scaler };
					// inside to outside
					if (clippedSV >= 0 && clippedEV < 0)
						clipCheckpoint.emplace_back(newV);
					// outside to inside
					else if (clippedSV < 0 && clippedEV >= 0) {
						clipCheckpoint.emplace_back(newV);
						clipCheckpoint.emplace_back(endVertex);
					}
				}
				buffers = clipCheckpoint;
			}
			if (!buffers.empty()) {
				for (auto& v : buffers)
					v = v.perspective();
				clippedPolygons.emplace_back(buffers);
			}
		}
		if (isNoBackfaces)
			clippedPolygons.erase(std::remove_if(clippedPolygons.begin(), clippedPolygons.end(),
				[](const auto& pg) {
					if (pg.size() < 3)
						return true;
					return (pg[1] - pg[0]).crossProduct(pg[2] - pg[1]).z >= 0;
				}), clippedPolygons.cend());
		const auto vp = ob.getViewport().getWindowViewPort(w, h);
		frame = { Point(vp.left, vp.top), Point(vp.left, vp.bottom), Point(vp.right, vp.bottom), Point(vp.right, vp.top) };
		const auto matrix = TransformMatrix(std::make_shared<const Translate>(vp.left, vp.bottom, 0)) *
			TransformMatrix(std::make_shared<const Scale>((vp.right - vp.left) / 2, (vp.top - vp.bottom) / 2, 0)) *
			TransformMatrix(std::make_shared<const Translate>(1, 1, 0));
		for (auto& pg : clippedPolygons)
			for (auto& v : pg)
				v = matrix * v;
	}

	std::ostream& operator<<(std::ostream& out, const Object& obj) {
		const auto pSize = obj.polygons.size();
		for (size_t i = 0; i < pSize; ++i) {
			out << "{";
			for (const auto& vertices : obj.polygons[i])
				out << vertices << ',';
			out << "\b}" << (i != pSize - 1 ? '\n' : '\0');
		}
		return out;
	}
}
