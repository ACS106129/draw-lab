#pragma once
#include <vector>
#include "base/Appendable.h"
#include "base/Drawable.h"
#include "base/Printable.h"
namespace draw {
	class Circle : public Appendable, public Drawable, public Printable {
	public:
		explicit Circle(const Dot&, const Color = Color::GREED);
		virtual void append() override;
		virtual void draw() const override;
		const Dot& getCircleCenter() const;
		const float getRadius() const;
	private:
		virtual void bufferingImpl(const Dot&) override;
		virtual void print(std::ostream&) const override;
		upLine radius;
		std::vector<upDot> dots;
	};
}

