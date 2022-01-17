#include <numeric>
#include <sstream>
#include "Command.h"
#include "../util/Util.h"

using namespace std;

namespace draw {
	Command::Command(const string& input) {
		if (input.rfind("clearData", 0) != string::npos)
			type = CommandType::CLEAR_DATA;
		else if (input.rfind("clearScreen", 0) != string::npos)
			type = CommandType::CLEAR_SCREEN;
		else if (input.rfind("# ", 0) != string::npos) {
			type = CommandType::COMMENT;
			args.emplace_back(input.substr(2));
		}
		else if (input.rfind("end", 0) != string::npos)
			type = CommandType::END;
		else if (input.rfind("reset", 0) != string::npos)
			type = CommandType::RESET;
		else if (input.rfind("rotate", 0) != string::npos) {
			type = CommandType::ROTATE;
			splitIntoArgs(input.substr(6));
		}
		else if (input.rfind("scale", 0) != string::npos) {
			type = CommandType::SCALE;
			splitIntoArgs(input.substr(5));
		}
		else if (input.rfind("square", 0) != string::npos)
			type = CommandType::SQUARE;
		else if (input.rfind("translate", 0) != string::npos) {
			type = CommandType::TRANSLATE;
			splitIntoArgs(input.substr(9));
		}
		else if (input.rfind("triangle", 0) != string::npos)
			type = CommandType::TRIANGLE;
		else if (input.rfind("view", 0) != string::npos) {
			type = CommandType::VIEW;
			splitIntoArgs(input.substr(4));
		}
		else
			throw new invalid_argument("Input: '" + input + "' dismatched command type!");
	}

	const CommandType Command::getType() const {
		return type;
	}

	const vector<string>& Command::getArgs() const {
		return args;
	}

	void Command::splitIntoArgs(const std::string& input) {
		std::stringstream ss(trim(input));
		std::string arg;
		while (std::getline(ss, arg, ' '))
			if (arg.length() > 0)
				args.emplace_back(arg);
	}

	ostream& operator<<(ostream& out, const Command& c) {
		return out << "Command{Type{" << c.type << "}" << (c.args.empty() ? "" : (", Args{" +
			std::accumulate(++c.args.cbegin(), c.args.cend(), *c.args.cbegin(),
				[](auto& a, const auto& b) { return a += "," + b; })) + "}") << "}";
	}
}
