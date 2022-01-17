#include <GL/glut.h>
#include <stdexcept>
#include "Dot.h"

using namespace draw;

Dot::Dot(const Dot& d) : Dot(d.x, d.y) {}
Dot::Dot(const Dot& d, const Color c) : Dot(d.x, d.y, c) {}
Dot::Dot(const int x, const int y, const Color c) : x(x), y(y), Drawable(c) {}

void Dot::draw() const {
	switch (color)
	{
	case Color::RED:
		glColor3f(1.0f, 0.0f, 0.0f);
		break;
	case Color::BLUE:
		glColor3f(0.0f, 0.0f, 1.0f);
		break;
	case Color::GREED:
		glColor3f(0.0f, 1.0f, 0.0f);
		break;
	case Color::YELLOW:
		glColor3f(1.0f, 1.0f, 0.0f);
		break;
	default:
		throw new std::invalid_argument("Error: Wrong color");
	}
	glBegin(GL_POINTS);
	glVertex2i(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
	glEnd();
}

void Dot::done() {}

const bool Dot::isDone() const {
	return true;
}

const int Dot::max() const {
	return std::max(x, y);
}

const int Dot::min() const {
	return std::min(x, y);
}

const float Dot::distance(const Dot& r) const {
	return static_cast<float>(std::sqrt(std::pow(x - r.x, 2) + std::pow(y - r.y, 2)));
}

void Dot::print(std::ostream& o) const {
	o << "Dot: (" << x << ", " << y << ")";
}

Dot Dot::operator+(const Dot& r) const {
	return Dot(x + r.x, y + r.y, color);
}

Dot Dot::operator-(const Dot& r) const {
	return Dot(x - r.x, y - r.y, color);
}

Dot Dot::operator*(const Dot& r) const {
	return Dot(x * r.x, y * r.y, color);
}

Dot Dot::operator/(const Dot& r) const {
	return Dot(x / r.x, y / r.y, color);
}

Dot& Dot::operator+=(const Dot& r) {
	return *this = *this + r;
}

Dot& Dot::operator-=(const Dot& r) {
	return *this = *this - r;
}

Dot& Dot::operator*=(const Dot& r) {
	return *this = *this * r;
}

Dot& Dot::operator/=(const Dot& r) {
	return *this = *this / r;
}

Dot& Dot::operator=(const Dot& r) {
	x = r.x;
	y = r.y;
	return *this;
}
