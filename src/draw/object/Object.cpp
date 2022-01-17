#include <GL/glut.h>
#include "Object.h"
#include "../Point.h"
#include "../color/Color.h"
#include "../matrix/eye/EyeMatrix.h"
#include "../matrix/transform/TransformMatrix.h"
#include "../object/Polygon.h"
#include "../transform/Scale.h"
#include "../transform/Translate.h"
#include "../util/RotationType.h"
#include "../view/Light.h"
#include "../view/Observer.h"
#include "../view/Shade.h"
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

	Object::Object(const Light& l, const std::vector<Polygon>& ps) : light(new Light(l)), polygons(ps), renderPolygons(ps) {}

	void Object::draw() const {
		if (renderPolygons.empty())
			return;
		for (const auto& pg : renderPolygons) {
			const auto size = pg.vertices.size();
			glColor3d(pg.shadingColor->r, pg.shadingColor->g, pg.shadingColor->b);
			glBegin(GL_LINE_STRIP);
			for (size_t c = 0; c < size + 1;) {
				const auto& p = pg.vertices[c++ % size];
				glVertex2d(p.x, p.y);
			}
			glEnd();
		}
	}

	void Object::reset() {
		renderPolygons = polygons;
	}

	const std::vector<Polygon>& Object::getRenderPolygons() const {
		return renderPolygons;
	}

	void Object::clipping(const int w, const int h, const Observer& ob) {
		const auto& obM = ob.getMatrix();
		std::vector<Point> buffers, clipCheckpoint;
		for (auto& rPolygon : renderPolygons) {
			const auto& vertices = rPolygon.vertices;
			const auto size = vertices.size();
			buffers.resize(size);
			// projection to buffers
			for (size_t i = 0; i < size; ++i)
				buffers[i] = obM * vertices[i];
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
				rPolygon.vertices = buffers;
			}
		}
		const auto vp = ob.getViewport().getWindowViewPort(w, h);
		const auto matrix = TransformMatrix(std::make_shared<const Translate>(vp.left, vp.bottom, 0)) *
			TransformMatrix(std::make_shared<const Scale>((vp.right - vp.left) / 2, (vp.top - vp.bottom) / 2, 1)) *
			TransformMatrix(std::make_shared<const Translate>(1, 1, 0));
		for (auto& pg : renderPolygons)
			for (auto& v : pg.vertices)
				v = matrix * v;
	}

	void Object::shading(const Observer& ob, const Shade& sh) {
		const auto Ic = sh.getAmbient() * *light->IPColor;
		const double Kd = light->IPos->x, Ks = light->IPos->y, N = light->IPos->z;
		for (auto& rPolygon : renderPolygons) {
			const auto normV = rPolygon.getNormalVertex(RotationType::CLOCKWISE).normalize();
			auto c = Ic;
			for (const auto& shL : sh.getLights()) {
				const auto lightV = *shL->IPos - rPolygon.vertices[0];
				const double normVLN = std::max(0.0, normV.innerProduct(lightV.normalize()));
				const double normELN = normVLN > 0 ?
					std::pow((*ob.getEyeMatrix().eye - rPolygon.vertices[0] + lightV).normalize().innerProduct(normV), N) : 0.0;
				c = c + (*shL->IPColor * *light->IPColor * (Kd * normVLN) + *shL->IPColor * (Ks * normELN));
			}
			rPolygon.shadingColor = std::make_shared<const Color>(c);
		}
	}

	std::ostream& operator<<(std::ostream& out, const Object& obj) {
		const auto pSize = obj.polygons.size();
		for (size_t i = 0; i < pSize; ++i) {
			out << "{";
			for (const auto& vertices : obj.polygons[i].vertices)
				out << vertices << ',';
			out << "\b}" << (i != pSize - 1 ? '\n' : '\0');
		}
		return out;
	}
}
