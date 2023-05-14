#ifndef __MATHHELPERS__H__
#define __MATHHELPERS__H__

/// <summary>
/// Classe auxiliar op matematicas
/// </summary>

class ivec2 {
public:
    int x, y;

    ivec2();
    ivec2(int _x, int _y);
};

class dvec2 {
public:
    double x, y;

    dvec2();
    dvec2(double _x, double _y);

    dvec2 operator/(const dvec2& other) const;    
    dvec2 operator/(const ivec2& other) const;
    dvec2 operator-(const dvec2& other) const;
    dvec2 operator+(const dvec2& other) const;
    dvec2 operator*(const dvec2& other) const;

};

#endif  // __MATHHELPERS__H__
