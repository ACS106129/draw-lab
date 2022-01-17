#include <filesystem>
#include "Reader.h"
#include "../Point.h"
#include "../command/Command.h"
#include "../object/Blueprint.h"
#include "../util/Util.h"

namespace draw {
	Reader::Reader(const int bs, const std::vector<std::string>& paths) : bufferSize(bs), buffer(new char[bs]) {
		for (const auto& path : paths.empty() ? listFiles("resources\\input\\", ".in") : paths) {
			commandFilenames.emplace_back(getFilename(path));
			for (const auto& e : read(path))
				commands.emplace_back(e);
		}
		if (commands.empty())
			throw std::runtime_error("Command is empty!");
		for (const auto& path : listFiles("resources\\asc\\", ".asc")) {
			const auto elems = read(path);
			const auto size = split(elems[0]);
			const size_t verticesCount = std::stoi(size[0]);
			const size_t facesCount = std::stoi(size[1]);
			auto obj = std::make_unique<Blueprint>(verticesCount, facesCount);
			size_t i = 1;
			for (size_t j = 0; j < verticesCount; ++i, ++j) {
				const auto splited = split(elems[i]);
				obj->addVertice(std::stod(splited[0]), std::stod(splited[1]), std::stod(splited[2]));
			}
			for (size_t j = 0; j < facesCount; ++i, ++j) {
				const auto splited = split(elems[i]);
				obj->addFace(std::stod(splited[1]), std::stod(splited[2]), std::stod(splited[3]),
					splited.size() == 5 ? std::stod(splited[4]) : 0);
			}
			bpMaps.emplace(getFilename(path), std::move(obj));
		}
	}

	const std::vector<std::string> Reader::listFiles(const std::string& dirPath, const std::string& suffix) const {
		std::vector<std::string> results;
		for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
			const auto filepath = entry.path().string();
			if (getFilename(filepath).find_last_of(suffix) == std::string::npos)
				continue;
			results.emplace_back(filepath);
		}
		return results;
	}

	const std::vector<std::string> Reader::read(const std::string& path) const {
		FILE* file;
		fopen_s(&file, path.c_str(), "r");
		if (!file)
			throw new std::runtime_error("File: " + path + " not found!");
		std::vector<std::string> elements;
		while (fgets(buffer, bufferSize, file)) {
			if (buffer[0] == '\n' || buffer[0] == '\0')
				continue;
			const size_t i = strlen(buffer) - 1;
			if (buffer[i] == '\n')
				buffer[i] = '\0';
			elements.emplace_back(buffer);
		}
		return elements;
	}

	const std::string& Reader::nextCommandFilename() {
		return commandFilenames[cmdFnIndex = (cmdFnIndex + 1) % commandFilenames.size()];
	}

	const Command& Reader::nextCommand() {
		return commands[cmdIndex = (cmdIndex + 1) % commands.size()];
	}

	const Command& Reader::peekCommand(const int offset) const {
		return commands[(cmdIndex + offset) % commands.size()];
	}

	const Blueprint& Reader::getBlueprint(const std::string& ascName) const {
		return *bpMaps.at(ascName);
	}
}