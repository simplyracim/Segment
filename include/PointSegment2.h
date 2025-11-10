#ifndef POINTSEGMENT2_H
#define POINTSEGMENT2_H

#include "Vector.h"
#include "Point2.h"

Point2 Point2_add(const Point2 *p, const Vector *r);
Vector Point2_sub(Point2 *r, const Point2 *p);

#endif