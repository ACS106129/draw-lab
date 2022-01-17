#pragma once
#include <memory>
#include <stdexcept>

namespace draw {
	static inline std::string lTrim(std::string s) {
		s.erase(s.cbegin(), std::find_if(s.cbegin(), s.cend(), [](const auto& c) { return !std::isspace(c); }));
		return s;
	}

	static inline std::string rTrim(std::string s) {
		s.erase(std::find_if(s.crbegin(), s.crend(), [](const auto& c) { return !std::isspace(c); }).base(), s.cend());
		return s;
	}

	static inline std::string trim(std::string s) {
		return rTrim(lTrim(s));
	}

	template<class T>
	static T getFilename(T const& path, T const& delims = "/\\") {
		return path.substr(path.find_last_of(delims) + 1);
	}

	template<typename ... Args>
	static std::string stringFormat(const std::string& format, const Args ... args) {
		const int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1;
		if (size_s <= 0)
			throw std::runtime_error("Error during formatting.");
		const auto size = static_cast<size_t>(size_s);
		const auto buf = std::make_unique<char[]>(size);
		std::snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1);
	}
}