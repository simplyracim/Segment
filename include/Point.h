#ifndef POINT_H
#define POINT_H

#include "Vector.h" // for vector_from_points(), translate()
#include <iostream>

class Point {
private:
    float x, y;

public:
    // constructors
    Point();
    Point(float new_x, float new_y);

    // getters
    float getX();
    float getY();

    // setters
    void setX(float new_x);
    void setY(float new_y);

    // print
    void print();
};

Vector vector_from_points(Point r, Point p);     // r - p
Point translate(Point p, Vector v);     // p + v

#endif // POINT_H