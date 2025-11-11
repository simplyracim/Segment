#ifndef SEGMENT2_H
#define SEGMENT2_H

#include "Point.h"
#include "Vector.h"

#include "PointSegment2.h"



typedef enum {
    POINT,
    COLINEAR_INTERSECTING,
    COLINEAR_NON_INTERSECTING,
    PARALLEL_NON_INTERSECTING,
    NON_INTERSECTING
} IntersectionStatus;

class Segment2 {

    public:
        Point origin;
        Vector direction;

        void Segment2_init(Segment2 *s, Point origin, Vector direction);
        Point Segment2_getOrigin(const Segment2 *s);
        Vector Segment2_getDirection(const Segment2 *s);
        float Segment2_length();
        IntersectionStatus Segment2_intersect(const Segment2 *s, const Segment2 *r, Point p);
        void Segment2_print(Segment2 *s);

};

const char* Segment2_statusToString(IntersectionStatus status);

#endif // SEGMENT2_H