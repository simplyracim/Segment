#include <stdio.h>
#include <stdlib.h>

#include "Point.h"
#include "Vector.h"
#include "Segment.h"

void drawScene(const Segment& s1, const Segment& s2, const Point* intersectionOpt);

#ifdef DEMONSTRATION

// Expected status: PARALLEL_NON_INTERSECTING
p1.Point(0., 0.);
p2.Point(1., 2.);
v1.Vector(1., 1.);
v2.Vector(2., 4.);

// Expected status: COLINEAR_INTERSECTING
p1.Point(0., 0.);
p2.Point(1., 0.);
v1.Vector(2., 0.);
v2.Vector(2., 0.);

// Expected intersection point: (1,0)
// Expected status: POINT
p1.Point(0., 0.);
p2.Point(1., -1.);
v1.Vector(2., 0.);
v2.Vector(0., 3.);

// Expected status: PARALLEL_NON_INTERSECTING
p1.Point(0., 0.);
p2.Point(1., 2.);
v1.Vector(1., 1.);
v2.Vector(2., 4.);

// Expected status: COLINEAR_INTERSECTING
p1.Point(0., 0.);
p2.Point(1., 0.);
v1.Vector(2., 0.);
v2.Vector(2., 0.);

// Expected status: COLINEAR_NON_INTERSECTING
p1.Point(0., 0.);
p2.Point(2., 0.);
v1.Vector(1., 0.);
v2.Vector(0., 1.);

// Expected status: NON_INTERSECTING
p1.Point(0., 0.);
p2.Point(2., 2.);
v1.Vector(1., 0.);
v2.Vector(-1., 1.);


p1.Point(0., 0.);
p2.Point(2., 0.);
v1.Vector(1., 0.);
v2.Vector(1., 0.);

#endif

int main() {
    
    // Insert Demo values here :
    Point p1(0., 0.);
    Point p2(2., 0.);
    Vector v1(1., 0.);
    Vector v2(0., 1.);

    Segment s1(p1, v1);
    Segment s2(p2, v2);

    Point intersection;

    std::cout << "Points 1 and 2 : \n";
    p2.print();
    p1.print();

    std::cout << "=====\n";

    std::cout << "Vectors 1 and 2 :\n";
    v1.print();
    v2.print();

    std::cout << "=====\n";

    std::cout << "Segments 1 and 2 : \n";
    s1.print();
    s2.print();

    std::cout << "=====\n";

    IntersectionStatus status = s1.intersect(s1, s2, intersection);

    std::cout << "\nIntersection status: "
              << Segment2_statusToString(status) << "\n";

    if (status == POINT) {
        std::cout << "Intersection point: ";
        intersection.print();
    }

    // Show the window with a point marker only when status == POINT
    drawScene(s1, s2, (status == POINT ? &intersection : nullptr));
    return 0;
}