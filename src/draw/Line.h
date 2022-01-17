#pragma once
#include <vector>
#include "base/Appendable.h"
#include "base/Drawable.h"
#include "base/Printable.h"
namespace draw {
	class Line : public Appendable, public Drawable, public Printable {
	public:
		/// <summary>
		/// Copy constructor
		/// </summary>
		Line(const Line&);
		explicit Line(const Line&, const Color);
		explicit Line(const Dot&, const Color = Color::BLUE);
		explicit Line(const Dot&, const Dot&, const Color = Color::BLUE);
		virtual void append() override;
		virtual void draw() const override;
		const Dot& getStartDot() const;
		const Dot& getEndDot() const;
	private:
		virtual bool doneFilter() override;
		virtual void bufferingImpl(const Dot&) override;
		virtual void print(std::ostream&) const override;
		std::vector<upDot> dots;
	};
}
