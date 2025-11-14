#ifndef POINT_H
#define POINT_H

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
    void print() const;
};

#endif // POINT_H