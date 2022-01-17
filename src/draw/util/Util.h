#pragma once
#include <memory>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace draw {
	static inline const std::string lTrim(std::string s) {
		s.erase(s.cbegin(), std::find_if(s.cbegin(), s.cend(), [](const auto& c) { return !std::isspace(c); }));
		return s;
	}

	static inline const std::string rTrim(std::string s) {
		s.erase(std::find_if(s.crbegin(), s.crend(), [](const auto& c) { return !std::isspace(c); }).base(), s.cend());
		return s;
	}

	static inline const std::string trim(const std::string& s) {
		return rTrim(lTrim(s));
	}

	static inline const std::vector<std::string> split(const std::string& input, const char delim = ' ') {
		std::vector<std::string> results;
		std::stringstream ss(trim(input));
		std::string elem;
		while (std::getline(ss, elem, delim))
			if (!elem.empty())
				results.emplace_back(elem);
		return results;
	}

	template<class T>
	static inline const T getFilename(const T& path, const T& delim = "/\\") {
		return path.substr(path.find_last_of(delim) + 1);
	}

	template<typename ... Args>
	static inline const std::string stringFormat(const std::string& format, const Args ... args) {
		const int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		if (size_s <= 0)
			throw std::runtime_error("Error during formatting.");
		const auto size = static_cast<size_t>(size_s);
		const auto buf = std::make_unique<char[]>(size);
		std::snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1);
	}
}