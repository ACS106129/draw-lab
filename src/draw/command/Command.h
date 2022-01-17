#pragma once
#include <vector>
#include "CommandType.h"

namespace draw {
	class Command {
	public:
		explicit Command(const std::string&);
		const CommandType getType() const;
		const std::vector<std::string>& getArgs() const;
	private:
		void splitIntoArgs(const std::string&);
		std::vector<std::string> args;
		CommandType type;
		friend std::ostream& operator<< (std::ostream&, const Command&);
	};
}
