#include "Math.h"
Vector2::Vector2():
	x(0.0f),
	y(0.0f)
{

}

Vector2::Vector2(float X, float Y) :
	x(X),
	y(Y)
{

}

Vector2 Vector2::Sum(Vector2 a, Vector2 b)
{
	return Vector2(a.x + b.x, a.y + b.y);
}

const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
const Vector2 Vector2::X = Vector2(1.0f, 0.0f);
const Vector2 Vector2::Y = Vector2(0.0f, 1.0f);
const Vector2 Vector2::NX = Vector2(-1.0f, 0.0f);
const Vector2 Vector2::NY = Vector2(0.0f, -1.0f);

Vector3::Vector3() :
	x(0.0f),
	y(0.0f),
	z(0.0f)
{

}

Vector3::Vector3(float X, float Y, float Z) :
	x(X),
	y(Y),
	z(Z)
{

}

float Mathf::Abs(float a)
{
	return (a >= 0) ? a : -a;
}

float Mathf::Max(float a, float b)
{
	return (a > b) ? a : b;
}

int Mathf::Max(int a, int b)
{
	return (a > b) ? a : b;
}

int Mathf::Min(int a, int b)
{
	return (a < b) ? a : b;
}