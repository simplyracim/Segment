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
        Point getOrigin();
        Vector getDirection();

        // operations
        float length();
        IntersectionStatus intersect(Segment s, Segment r, Point p);
        void print();

};

const char* Segment2_statusToString(IntersectionStatus status);

#endif // SEGMENT_H