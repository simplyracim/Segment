#ifndef VECTOR_H
#define VECTOR_H

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
    float length();
    float dot(Vector r);
    float cross(Vector r);
    Vector dot_scalar(float u);
    Vector negate();

    void print();
};

#endif // VECTOR_H
