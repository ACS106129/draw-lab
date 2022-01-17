#pragma once
#include <ostream>

namespace draw {
	enum class Color {
		WHITE,
		YELLOW
	};

	inline std::ostream& operator<< (std::ostream& out, const Color& type) {
		const char* s = 0;
#define PROCESS_VAL(p) case(Color::p): s = #p; break;
		switch (type) {
			PROCESS_VAL(WHITE);
			PROCESS_VAL(YELLOW);
		}
#undef PROCESS_VAL
		return out << s;
	}
}
