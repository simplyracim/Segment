#include "Point2.h"

// constructors
void Point2::Point2_init(Point2 *p) {
    p->x = 0;
    p->y = 0;
}

void Point2::Point2_init_with_xy(Point2 *p, float x, float y) {
    p->x = x;
    p->y = y;
}

// getters
float Point2::Point2_getX(const Point2 *p) const {
    return p->x;
}

float Point2::Point2_getY(const Point2 *p) const {
    return p->y;
}

// setters
void Point2::Point2_setX(Point2 *p, float x) {
    p->x = x;
}

void Point2::Point2_setY(Point2 *p, float y) {
    p->y = y;
}

// print
void Point2::Point2_print(const Point2 *p) const {
    std::cout << "{" << p->x << " , " << p->y << "}\n";
}

Vector Point2_sub(Point2* r, const Point2* p) {
    const float dx = r->Point2_getX(r) - p->Point2_getX(p);
    const float dy = r->Point2_getY(r) - p->Point2_getY(p);
    return Vector(dx, dy);
}

Point2 Point2_add(const Point2* p, const Vector* v) {
    Point2 result;
    const float x = p->Point2_getX(p) + v->getX();
    const float y = p->Point2_getY(p) + v->getY();
    result.Point2_init_with_xy(&result, x, y);
    return result;
}