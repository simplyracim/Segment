#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"

#include <cmath>
#include <iostream>

class Vector {
private :
    float x, y;

public :
    // Constructors
    Vector();
    Vector(float x, float y);

    // Accessors
    float getX();
    float getY();

    // Operations
    float length() const;
    float dot(Vector r) const;
    float cross(Vector r) const;
    Vector dot_scalar(float u) const;
    Vector negate();

    void print() const;
};

Vector vector_from_points(Point a, Point b);
Point translate(Point p, Vector v);

#endif // VECTOR_H
