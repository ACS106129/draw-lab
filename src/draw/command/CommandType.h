#pragma once
#include <algorithm>
#include <ostream>

namespace draw {
	enum class CommandType {
		COMMENT,
		DISPLAY,
		END,
		NOBACKFACES,
		OBJECT,
		OBSERVER,
		RESET,
		RESHAPE,
		ROTATE,
		SCALE,
		TRANSLATE,
		VIEWPORT
	};

	inline std::ostream& operator<< (std::ostream& out, const CommandType& type) {
		std::string s;
#define PROCESS_VAL(p) case(CommandType::p): s = #p; break;
		switch (type) {
			PROCESS_VAL(COMMENT);
			PROCESS_VAL(DISPLAY);
			PROCESS_VAL(END);
			PROCESS_VAL(NOBACKFACES);
			PROCESS_VAL(OBJECT);
			PROCESS_VAL(OBSERVER);
			PROCESS_VAL(RESET);
			PROCESS_VAL(ROTATE);
			PROCESS_VAL(SCALE);
			PROCESS_VAL(TRANSLATE);
			PROCESS_VAL(VIEWPORT);
		}
#undef PROCESS_VAL
		std::transform(++s.cbegin(), s.cend(), ++s.begin(), [](const auto& c) { return std::tolower(c); });
		return out << s;
	}
}