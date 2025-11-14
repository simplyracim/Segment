#ifndef SEGMENT_H
#define SEGMENT_H

#include "Point.h"
#include "Vector.h"

typedef enum {
    POINT,
    COLINEAR_INTERSECTING,
    COLINEAR_NON_INTERSECTING,
    PARALLEL_NON_INTERSECTING,
    NON_INTERSECTING
} IntersectionStatus;

class Segment {

    private :

    public :
        Point origin;
        Vector direction;

        // constructor
        Segment(Point origin, Vector direction);

        // getters
        Point getOrigin() const;
        Vector getDirection() const;

        // operations
        float length() const;
        IntersectionStatus intersect(const Segment& other, Point& p) const;
        void print() const;

};

const char* Segment2_statusToString(IntersectionStatus status);

#endif // SEGMENT_H