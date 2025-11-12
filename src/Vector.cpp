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
float Vector::length() {
    return std::sqrt(x * x + y * y);
}

float Vector::dot(Vector r) {
    // allowed to access r.x / r.y because we're inside Vector's member function
    return this->x * r.x + this->y * r.y;
}

float Vector::cross(Vector r) {
    // 2D "cross" returns a scalar (z-component of the 3D cross product)
    return this->x * r.y - this->y * r.x;
}

Vector Vector::dot_scalar(float u) {
    return Vector(x * u, y * u);
}

Vector Vector::negate() {
    return Vector(-x, -y);
}

void Vector::print() {
    std::cout << "Vector(" << x << ", " << y << ")\n";
}