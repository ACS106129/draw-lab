#pragma once
#include <map>
#include <string>
#include <vector>

namespace draw {
	class Command;
	class Blueprint;
	class Reader {
	public:
		explicit Reader(const int, const std::vector<std::string>&);
		const std::string& nextCommandFilename();
		const Command& nextCommand();
		const Command& peekCommand(const int = 1) const;
		const Blueprint& getBlueprint(const std::string&) const;
		const int bufferSize;
	private:
		const std::vector<std::string> listFiles(const std::string&, const std::string&) const;
		const std::vector<std::string> read(const std::string&) const;
		int cmdIndex = -1;
		int cmdFnIndex = -1;
		char* buffer;
		std::vector<Command> commands;
		std::vector<std::string> commandFilenames;
		std::map<std::string, std::unique_ptr<Blueprint>> bpMaps;
	};
}
