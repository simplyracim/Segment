#include "Point.h"

// contructeurs
Point::Point() : x(0.f), y(0.f) {}
Point::Point(float new_x, float new_y) : x(new_x), y(new_y) {}

// getters
float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

// setters
void Point::setX(float new_x) {
    x = new_x;
}

void Point::setY(float new_y) {
    y = new_y;
}

// print
void Point::print() const {
    std::cout << "{" << x << " , " << y << "}\n";
}