#ifndef POINT2_H
#define POINT2_H

#include "Vector.h"
#include <iostream>

class Point2 {
    
    private :

        float x, y;

    public:

        // constructors
        void Point2_init(Point2 *p);
        void Point2_init_with_xy(Point2 *p, float x, float y);

        // getters
        float Point2_getX(const Point2 *p) const;
        float Point2_getY(const Point2 *p) const;

        // setters
        void Point2_setX(Point2 *p, float x);
        void Point2_setY(Point2 *p, float y);

        // print
        void Point2_print(const Point2 *p) const;
};

#endif // POINT2_H