#ifndef MATHHELPERS_H
#define MATHHELPERS_H

/// <summary>
/// Classe auxiliar
/// </summary>

class Vector2 {
public:
    double x, y;

    Vector2();
    Vector2(double _x, double _y);

    Vector2 operator/(const Vector2& other) const;    
    Vector2 operator-(const Vector2& other) const;
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator*(const Vector2& other) const;

};

class Int2 {
public:
    int x, y;

    Int2();
    Int2(int _x, int _y);    
};


#endif  // MATHHELPERS_H
