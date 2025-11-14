// Vector.cpp
#include "Vector.h"

#include <cmath>      // std::sqrt
#include <iostream>

// contructeurs
Vector::Vector() : x(0.f), y(0.f) {}
Vector::Vector(float new_x, float new_y) : x(new_x), y(new_y) {}

// getters
float Vector::getX() { return x; }
float Vector::getY() { return y; }

// operations
float Vector::length() const {
    return std::sqrt(x * x + y * y);
}

float Vector::dot(Vector r) const {
    // allowed to access r.x / r.y because we're inside Vector's member function
    return this->x * r.x + this->y * r.y;
}

// determinant
float Vector::cross(Vector r) const {
    return this->x * r.y - this->y * r.x;
}

Vector Vector::dot_scalar(float u) const {
    return Vector(x * u, y * u);
}

Vector Vector::negate() {
    return Vector(-x, -y);
}

void Vector::print() const {
    std::cout << "Vector(" << x << ", " << y << ")\n";
}

// Create a vector from two points
Vector vector_from_points(Point a, Point b) {

    float dx = a.getX() - b.getX();
    float dy = a.getY() - b.getY();

    return Vector(dx, dy);
}

// add a point at origin.x + vector.x ; origin.y + vector.y
Point translate(Point p, Vector v) {

    Point result;
    float x = p.getX() + v.getX();
    float y = p.getY() + v.getY();

    return Point(x, y);
}