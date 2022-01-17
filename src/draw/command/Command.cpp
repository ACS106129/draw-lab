#include <numeric>
#include <sstream>
#include "Command.h"
#include "../util/Util.h"

namespace draw {
	Command::Command(const std::string& input) {
		if (tryEmplaceKeyword(input, "# ", -1))
			type = CommandType::COMMENT;
		else if (tryEmplaceKeyword(input, "display"))
			type = CommandType::DISPLAY;
		else if (tryEmplaceKeyword(input, "end"))
			type = CommandType::END;
		else if (tryEmplaceKeyword(input, "nobackfaces"))
			type = CommandType::NOBACKFACES;
		else if (tryEmplaceKeyword(input, "object", 1))
			type = CommandType::OBJECT;
		else if (tryEmplaceKeyword(input, "observer", 10))
			type = CommandType::OBSERVER;
		else if (tryEmplaceKeyword(input, "reset"))
			type = CommandType::RESET;
		else if (tryEmplaceKeyword(input, "rotate", 3))
			type = CommandType::ROTATE;
		else if (tryEmplaceKeyword(input, "scale", 3))
			type = CommandType::SCALE;
		else if (tryEmplaceKeyword(input, "translate", 3))
			type = CommandType::TRANSLATE;
		else if (tryEmplaceKeyword(input, "viewport", 4))
			type = CommandType::VIEWPORT;
		else {
			const auto arguments = split(input);
			if (arguments.size() == 2)
				type = CommandType::RESHAPE;
			else
				throw new std::runtime_error("Input: '" + input + "' dismatched command type!");
			for (const auto arg : arguments)
				args.emplace_back(arg);
		}
	}

	const CommandType Command::getType() const {
		return type;
	}

	const std::vector<std::string>& Command::getArgs() const {
		return args;
	}

	const bool Command::tryEmplaceKeyword(const std::string& input, const std::string& keyword, const int argsOption) {
		// 0 ~ n argument, default 0 should not exist any arguments
		// -1 regarded as 1 argument, but no split the input by delimiter
		if (input.rfind(keyword, 0) == std::string::npos)
			return false;
		if (argsOption == -1)
			args.emplace_back(input.substr(keyword.length()));
		else if (argsOption > 0)
			for (const auto arg : split(input.substr(keyword.length())))
				args.emplace_back(arg);
		const size_t size = argsOption == -1 ? 1 : argsOption;
		if (args.size() != size)
			throw std::runtime_error(stringFormat("Argument size [%d] is not matched required [%d]", args.size(), size));
		return true;
	}

	std::ostream& operator<<(std::ostream& out, const Command& c) {
		return out << "Command{Type{" << c.type << "}" << (c.args.empty() ? "" : (", Args{" +
			std::accumulate(++c.args.cbegin(), c.args.cend(), *c.args.cbegin(),
				[](auto& a, const auto& b) { return a += "," + b; })) + "}") << "}";
	}
}
