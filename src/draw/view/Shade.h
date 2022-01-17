#pragma once
#include <memory>
#include <vector>

namespace draw {
	class Color;
	class Light;
	class Shade {
	public:
		explicit Shade();
		void reset();
		void setAmbient(const Color&);
		void setBackground(const Color&);
		void addLight(const size_t, const Light&);
		const Color& getAmbient() const;
		const Color& getBackground() const;
		const std::vector<std::unique_ptr<const Light>>& getLights() const;
	private:
		std::unique_ptr<const Color> ambient;
		std::unique_ptr<const Color> background;
		std::vector<std::unique_ptr<const Light>> lights;
	};
}
