#include <GL/glut.h>
#include "Observer.h"
#include "Scene.h"
#include "Shade.h"
#include "../Point.h"
#include "../color/Color.h"
#include "../matrix/eye/EyeMatrix.h"
#include "../matrix/projection/ProjectionMatrix.h"
#include "../object/Object.h"
#include "../object/Polygon.h"
#include "../util/RotationType.h"
#include "../view/Light.h"
#include "../view/ViewPort.h"

namespace draw {
	Scene::Scene() : observer(new Observer), shade(new Shade) {}

	void Scene::clearObjects() {
		objects.clear();
		renderPolygons.clear();
	}

	void Scene::update(const int w, const int h) {
		wvp = std::make_unique<const ViewPort>(observer->getViewport().getWindowViewPort(w, h));
		frame = { Point(wvp->left, wvp->top), Point(wvp->left, wvp->bottom), Point(wvp->right, wvp->bottom), Point(wvp->right, wvp->top) };
		renderPolygons.clear();
		for (const auto& o : objects) {
			o->reset();
			o->shading(*observer, *shade);
			o->clipping(w, h, *observer);
			const auto& polys = o->getRenderPolygons();
			renderPolygons.insert(renderPolygons.cend(), polys.cbegin(), polys.cend());
		}
		cBuffers.resize(w);
		zBuffers.resize(w);
		std::fill(cBuffers.begin(), cBuffers.end(), std::vector<Color>(h, shade->getBackground()));
		std::fill(zBuffers.begin(), zBuffers.end(), std::vector<double>(h, std::numeric_limits<double>::max()));
		for (const auto& rPolygon : renderPolygons) {
			const auto norm = rPolygon.getNormalVertex(RotationType::COUNTERCLOCKWISE).normalize();
			const double np = norm.innerProduct(rPolygon.vertices[0]);
			for (auto [y, yMax] = rPolygon.getMinMax(Axis::Y); y != yMax; ++y) {
				auto [x, xMax] = rPolygon.getMinMax(Axis::X);
				for (double z = (np - norm.x * x - norm.y * y) / norm.z; x != xMax; ++x, z -= norm.x / norm.z) {
					if (z < zBuffers[y][x] && rPolygon.contains(x, y, norm)) {
						zBuffers[y][x] = z;
						cBuffers[y][x] = *rPolygon.shadingColor;
					}
				}
			}
		}
	}

	void Scene::draw() const {
		if (renderPolygons.empty())
			return;
		glBegin(GL_POINTS);
		for (double y = wvp->bottom; y < wvp->top; ++y)
			for (double x = wvp->left; x < wvp->right; ++x) {
				const auto& c = cBuffers[static_cast<int>(y)][static_cast<int>(x)];
				glColor3d(c.r, c.g, c.b);
				glVertex2d(x, y);
			}
		glEnd();
	}

	void Scene::addObject(std::unique_ptr<Object>&& o) {
		objects.emplace_back(std::move(o));
	}
}
