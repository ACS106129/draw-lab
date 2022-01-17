#pragma once
#include <vector>
#include "base/Appendable.h"
#include "base/Drawable.h"
#include "base/Printable.h"
namespace draw {
	class Polygon : public Appendable, public Drawable, public Printable {
	public:
		explicit Polygon(const Dot&, const Color = Color::YELLOW);
		virtual void append() override;
		virtual void draw() const override;
		const std::vector<Dot> getDots() const;
	private:
		virtual void bufferingImpl(const Dot&) override;
		virtual bool doneFilter() override;
		virtual void print(std::ostream&) const override;
		std::vector<upLine> lines;
	};
}
