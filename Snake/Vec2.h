#pragma once

class Vec2 {
public:
	Vec2() = default;
	Vec2(float xIn, float yIn);
	Vec2 operator+(const Vec2& rhs) const;
	Vec2& operator+=(const Vec2& rhs);
	Vec2 operator-(const Vec2& rhs) const;
	Vec2& operator-=(const Vec2& rhs);
	Vec2 operator*(float rhs) const;
	Vec2& operator*=(float rhs);
	bool operator==(const Vec2& rhs) const;
	bool operator!=(const Vec2& rhs) const;
	float GetLength() const;
	float GetLengthSq() const;
	Vec2& Normalize();
	Vec2 GetNormalized() const;
public:
	float x;
	float y;
};