#ifndef POINT2_H
#define POINT2_H

#include "Vector.h" // for point2_sub, point2_add
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

#endif // POINT2_H