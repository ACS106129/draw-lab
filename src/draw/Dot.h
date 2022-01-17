#pragma once
#include "base/Drawable.h"
#include "base/Printable.h"
#include "impl/ICompletable.h"
namespace draw {
	class Dot : public Drawable, public ICompletable, public Printable {
	public:
		/// <summary>
		/// Copy Constructor
		/// </summary>
		Dot(const Dot&);
		explicit Dot(const Dot&, const Color);
		explicit Dot(const int, const int, const Color = Color::RED);
		virtual void done() override;
		virtual void draw() const override;
		virtual const bool isDone() const override;
		/// <returns>Max value of axis</returns>
		const int max() const;
		/// <returns>Min value of axis</returns>
		const int min() const;
		/// <summary>
		/// Evaluate the distance to another dot
		/// </summary>
		/// <param name="Dot">to be evaluated with</param>
		/// <returns></returns>
		const float distance(const Dot & = Dot(0, 0)) const;
		Dot operator+(const Dot&) const;
		Dot operator-(const Dot&) const;
		Dot operator*(const Dot&) const;
		Dot operator/(const Dot&) const;
		Dot& operator+=(const Dot&);
		Dot& operator-=(const Dot&);
		Dot& operator*=(const Dot&);
		Dot& operator/=(const Dot&);
		Dot& operator=(const Dot&);
		int x, y;
	private:
		virtual void print(std::ostream&) const override;
	};
}