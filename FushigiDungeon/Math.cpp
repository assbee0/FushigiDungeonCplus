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
