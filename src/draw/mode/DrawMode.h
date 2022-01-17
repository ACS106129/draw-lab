#pragma once
#include <ostream>
namespace draw {
	/// <summary>
	///  DrawMode for draw mode switching
	/// </summary>
	enum class DrawMode {
		NONE,
		CIRCLE,
		DOT,
		LINE,
		POLYGON
	};

	inline constexpr std::ostream& operator<<(std::ostream& o, DrawMode mode) {
		switch (mode)
		{
		case draw::DrawMode::NONE:
			o << "None";
			break;
		case draw::DrawMode::CIRCLE:
			o << "Cicle";
			break;
		case draw::DrawMode::DOT:
			o << "Dot";
			break;
		case draw::DrawMode::LINE:
			o << "Line";
			break;
		case draw::DrawMode::POLYGON:
			o << "Polygon";
			break;
		default:
			throw new std::invalid_argument("Error: Wrong drawmode");
		}
		return o;
	}
}