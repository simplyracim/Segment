#include "Point2.h"

void Point2::Point2_init(Point2 *p) {
    p->x = 0;
    p->y = 0;
}

void Point2::Point2_init_with_xy(Point2 *p, float x, float y) {
    p->x = x;
    p->y = y;
}

float Point2::Point2_getX(const Point2 *p) const {
    return p->x;
}

float Point2::Point2_getY(const Point2 *p) const {
    return p->y;
}

void Point2::Point2_setX(Point2 *p, float x) {
    p->x = x;
}

void Point2::Point2_setY(Point2 *p, float y) {
    p->y = y;
}

void Point2::Point2_print(const Point2 *p) const {
    // printf("{%f, %f}\n", p->x, p->y);
    std::cout << "{" << p->x << " , " << p->y << "}\n";
}

Vector2 Point2_sub(Point2* r, const Point2* p) {
    Vector2 result;
    const float dx = r->Point2_getX(r) - p->Point2_getX(p);
    const float dy = r->Point2_getY(r) - p->Point2_getY(p);
    result.Vector2_init(&result, dx, dy);
    return result;
}

Point2 Point2_add(const Point2* p, const Vector2* v) {
    Point2 result;
    const float x = p->Point2_getX(p) + v->Vector2_getX(v);
    const float y = p->Point2_getY(p) + v->Vector2_getY(v);
    result.Point2_init_with_xy(&result, x, y);
    return result;
}