#pragma once
class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float X, float Y);

	static Vector2 Sum(Vector2 a, Vector2 b);

	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 X;
	static const Vector2 Y;
	static const Vector2 NX;
	static const Vector2 NY;

	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	friend Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	friend bool operator==(const Vector2& a, const Vector2& b)
	{
		return (a.x == b.x && a.y == b.y);
	}
};
