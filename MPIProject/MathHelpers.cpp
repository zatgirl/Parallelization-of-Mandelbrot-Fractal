#include "MathHelpers.h"

dvec2::dvec2()
{
    this->x = this->y = 0.0f;
}

dvec2::dvec2(double _x, double _y)
{
    x = _x;
    y = _y;
}

dvec2 dvec2::operator/(const dvec2& other) const {
    return dvec2(x / other.x, y / other.y);
}

dvec2 dvec2::operator-(const dvec2& other) const {
    return dvec2(x - other.x, y - other.y);
}

dvec2 dvec2::operator+(const dvec2& other) const {
    return dvec2(x + other.x, y + other.y);
}

dvec2 dvec2::operator*(const dvec2& other) const {
    return dvec2(x * other.x, y * other.y);
}

ivec2::ivec2()
{
    this->x = this->y = 0;
}

ivec2::ivec2(int _x, int _y)
{
    x = _x;
    y = _y;
}

dvec2 dvec2::operator/(const ivec2& other) const {
    return dvec2(x / other.x, y / other.y);
}


