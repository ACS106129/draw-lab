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
		const bool tryEmplaceKeyword(const std::string&, const std::string&, const int = 0);
		std::vector<std::string> args;
		CommandType type;
		friend std::ostream& operator<< (std::ostream&, const Command&);
	};
}
