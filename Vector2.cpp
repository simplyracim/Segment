#include <iostream>
#include "Vector2.h"

void Vector2::Vector2_init(Vector2 *v, float x, float y) {
    v->x = x;
    v->y = y;
}

float Vector2::Vector2_getX(const Vector2 *v) const {
    return v->x;
}

float Vector2::Vector2_getY(const Vector2 *v) const {
    return v->y;
}

float Vector2::Vector2_norm(const Vector2 *v) const {
    return sqrt(v->x * v->x + v->y * v->y);
}

float Vector2::Vector2_dot(const Vector2 *v, const Vector2 *r) {
    return v->x * r->x + v->y * r->y;
}

Vector2 Vector2::Vector2_dot_scalar(const Vector2 *v, float u) {
    Vector2 result;
    Vector2_init(&result, u * v->x, u * v->y);
    return result;
}

float Vector2::Vector2_cross(const Vector2 *v, const Vector2 *r) {
    return (v->x * r->y) - (v->y * r->x);
}

Vector2 Vector2::Vector2_negate(const Vector2 *v) {
    Vector2 result;
    Vector2_init(&result, -v->x, -v->y);
    return result;
}

void Vector2::Vector2_print(const Vector2 *v) const {
    std::cout << "Vector(" << v->x << ", " << v->y << ")\n";
}