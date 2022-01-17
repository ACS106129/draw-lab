#pragma once
#include <ostream>

namespace draw {
	enum class CommandType {
		CLEAR_DATA,
		CLEAR_SCREEN,
		COMMENT,
		END,
		RESET,
		ROTATE,
		SCALE,
		SQUARE,
		TRANSLATE,
		TRIANGLE,
		VIEW
	};

	inline std::ostream& operator<< (std::ostream& out, const CommandType& type) {
		const char* s = 0;
#define PROCESS_VAL(p) case(CommandType::p): s = #p; break;
		switch (type) {
			PROCESS_VAL(CLEAR_DATA);
			PROCESS_VAL(CLEAR_SCREEN);
			PROCESS_VAL(COMMENT);
			PROCESS_VAL(END);
			PROCESS_VAL(RESET);
			PROCESS_VAL(ROTATE);
			PROCESS_VAL(SCALE);
			PROCESS_VAL(SQUARE);
			PROCESS_VAL(TRANSLATE);
			PROCESS_VAL(TRIANGLE);
			PROCESS_VAL(VIEW);
		}
#undef PROCESS_VAL
		return out << s;
	}
}