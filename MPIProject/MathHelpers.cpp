#include "MathHelpers.h"

Vector2::Vector2()
{
    this->x = this->y = 0.0f;
}

Vector2::Vector2(double _x, double _y)
{
    x = _x;
    y = _y;
}

Vector2 Vector2::operator/(const Vector2& other) const {
    return Vector2(x / other.x, y / other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator*(const Vector2& other) const {
    return Vector2(x * other.x, y * other.y);
}

Int2::Int2()
{
    this->x = this->y = 0;
}

Int2::Int2(int _x, int _y)
{
    x = _x;
    y = _y;
}


