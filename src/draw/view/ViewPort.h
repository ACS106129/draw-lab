#pragma once
#include <ostream>

namespace draw {
	class ViewPort {
	public:
		explicit ViewPort(const double = 0.0, const double = 0.0, const double = 0.0, const double = 0.0);
		const ViewPort getWindowViewPort(const int, const int) const;
		const double left;
		const double right;
		const double bottom;
		const double top;
		virtual ~ViewPort() = default;
	private:
		friend std::ostream& operator<< (std::ostream&, const ViewPort&);
	};
}
