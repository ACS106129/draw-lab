#pragma once
#include <ostream>

namespace draw {
	enum class RotationType {
		CLOCKWISE,
		COUNTERCLOCKWISE
	};

	inline std::ostream& operator<< (std::ostream& out, const RotationType& type) {
		const char* s = 0;
#define PROCESS_VAL(p) case(RotationType::p): s = #p; break;
		switch (type) {
			PROCESS_VAL(CLOCKWISE);
			PROCESS_VAL(COUNTERCLOCKWISE);
		}
#undef PROCESS_VAL
		return out << s;
	}
}
