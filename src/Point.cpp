#include "Point.h"

// contructeurs
Point::Point() : x(0.f), y(0.f) {}
Point::Point(float new_x, float new_y) : x(new_x), y(new_y) {}

// getters
float Point::getX() {
    return x;
}

float Point::getY() {
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
void Point::print() {
    std::cout << "{" << x << " , " << y << "}\n";
}


// Create a vector from two points
Vector vector_from_points(Point r, Point p) {

    float dx = r.getX() - p.getX();
    float dy = r.getY() - p.getY();

    return Vector(dx, dy);
}

// add a point at origin.x + vector.x ; origin.y + vector.y
Point translate(Point p, Vector v) {

    Point result;
    float x = p.getX() + v.getX();
    float y = p.getY() + v.getY();

    return Point(x, y);
}