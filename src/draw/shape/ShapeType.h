#pragma once
#include <algorithm>
#include <ostream>

namespace draw {
	enum class ShapeType {
		SQUARE = 4,
		TRIANGLE = 3
	};

	inline std::ostream& operator<< (std::ostream& out, const ShapeType& type) {
		std::string s;
#define PROCESS_VAL(p) case(ShapeType::p): s = #p; break;
		switch (type) {
			PROCESS_VAL(SQUARE);
			PROCESS_VAL(TRIANGLE);
		}
#undef PROCESS_VAL
		std::transform(++s.cbegin(), s.cend(), ++s.begin(), [](const auto& c) { return std::tolower(c); });
		return out << s;
	}
}