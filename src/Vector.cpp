// Vector.cpp
#include "Vector.h"

#include <cmath>      // std::sqrt
#include <iostream>

// contructeurs
Vector::Vector() : x(0.f), y(0.f) {}
Vector::Vector(float new_x, float new_y) : x(new_x), y(new_y) {}

// getters
float Vector::getX() const { return x; }
float Vector::getY() const { return y; }

// operations
float Vector::norm() const {
    return std::sqrt(x * x + y * y);
}

float Vector::dot(const Vector& r) const {
    // allowed to access r.x / r.y because we're inside Vector's member function
    return x * r.x + y * r.y;
}

Vector Vector::dot_scalar(float u) const {
    return Vector(x * u, y * u);
}

float Vector::cross(const Vector& r) const {
    // 2D "cross" returns a scalar (z-component of the 3D cross product)
    return x * r.y - y * r.x;
}

Vector Vector::negate() const {
    return Vector(-x, -y);
}

void Vector::print() const {
    std::cout << "Vector(" << x << ", " << y << ")\n";
}
