#pragma once
#include <ostream>
namespace draw {
	class Printable {
	public:
		friend std::ostream& operator<< (std::ostream& out, const Printable& p) {
			p.print(out);
			return out;
		}
	protected:
		/// <summary>
		/// Make object can be print as string
		/// </summary>
		/// <param name="">Output stream</param>
		virtual void print(std::ostream&) const = 0;
	};
}