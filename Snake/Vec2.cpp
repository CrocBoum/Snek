#include "Vec2.h"
#include <cmath>


Vec2::Vec2(float xIn, float yIn) :
	x(xIn),
	y(yIn) {}

Vec2 Vec2::operator+(const Vec2& rhs) const {
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2& Vec2::operator+=(const Vec2& rhs) {
	return *this = *this + rhs;
}

Vec2 Vec2::operator-(const Vec2& rhs) const {
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2& Vec2::operator-=(const Vec2& rhs) {
	return *this = *this - rhs;
}

Vec2 Vec2::operator*(float rhs) const {
	return Vec2(x * rhs, y * rhs);
}

Vec2& Vec2::operator*=(float rhs) {
	return *this = *this * rhs;
}

bool Vec2::operator==(const Vec2& rhs) const {
	return x == rhs.x && y == rhs.y;
}

bool Vec2::operator!=(const Vec2& rhs) const {
	return x != rhs.x || y != rhs.y;
}

float Vec2::GetLength() const {
	return std::sqrt(GetLengthSq());
}

float Vec2::GetLengthSq() const {
	return x * x + y * y;
}

Vec2& Vec2::Normalize() {
	return *this = GetNormalized();
}

Vec2 Vec2::GetNormalized() const {
	const float len = GetLength();
	if (len != 0.0f) {
		return *this * (1.0f / len);
	}
	return *this;
}