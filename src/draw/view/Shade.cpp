#include "Shade.h"
#include "Light.h"
#include "../Point.h"
#include "../color/Color.h"

namespace draw {
	Shade::Shade() : background(new Color(Color::BLACK)) {}

	void Shade::reset() {
		ambient = nullptr;
		background = std::make_unique<const Color>(Color::BLACK);
		lights.clear();
	}

	void Shade::setAmbient(const Color& c) {
		ambient = std::make_unique<const Color>(c);
	}

	void Shade::setBackground(const Color& c) {
		background = std::make_unique<const Color>(c);
	}

	void Shade::addLight(const size_t i, const Light& l) {
		if (i < lights.size())
			lights[i] = std::make_unique<const Light>(l);
		else
			lights.emplace_back(new Light(l));
	}
	const Color& Shade::getAmbient() const {
		return *ambient;
	}

	const Color& Shade::getBackground() const {
		return *background;
	}

	const std::vector<std::unique_ptr<const Light>>& Shade::getLights() const {
		return lights;
	}
}