#ifndef SEGMENT2_H
#define SEGMENT2_H

#include "Point2.h"
#include "Vector2.h"

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
        Point2 origin;
        Vector2 direction;

        void Segment2_init(Segment2 *s, Point2 origin, Vector2 direction);
        Point2 Segment2_getOrigin(const Segment2 *s);
        Vector2 Segment2_getDirection(const Segment2 *s);
        float Segment2_length(const Segment2 *s);
        IntersectionStatus Segment2_intersect(const Segment2 *s, const Segment2 *r, Point2 *p);
        void Segment2_print(Segment2 *s);

};

const char* Segment2_statusToString(IntersectionStatus status);

#endif // SEGMENT2_H