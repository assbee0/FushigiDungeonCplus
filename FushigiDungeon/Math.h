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
};
