#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

class Vector {
private:
    float x, y;

public:
    // Constructors
    Vector();
    Vector(float x, float y);

    // Accessors
    float getX() const;
    float getY() const;

    // Operations
    float norm() const;

    float dot(const Vector& r) const;

    Vector dot_scalar(float u) const;

    float cross(const Vector& r) const;

    Vector negate() const;

    void print() const;
};

#endif // VECTOR_H
