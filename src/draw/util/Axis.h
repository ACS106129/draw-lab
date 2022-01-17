#pragma once
#include <ostream>

namespace draw {
	enum class Axis {
		X,
		Y,
		Z
	};

	inline std::ostream& operator<< (std::ostream& out, const Axis& type) {
		const char* s = 0;
#define PROCESS_VAL(p) case(Axis::p): s = #p; break;
		switch (type) {
			PROCESS_VAL(X);
			PROCESS_VAL(Y);
			PROCESS_VAL(Z);
		}
#undef PROCESS_VAL
		return out << s;
	}
}
