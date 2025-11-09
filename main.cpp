#include <stdio.h>
#include <stdlib.h>

#include "Point2.h"
#include "Vector2.h"
#include "Segment2.h"

#ifdef DEMONSTRATION

p1.Point2_init_with_xy(&p1, 0., 0.);
p2.Point2_init_with_xy(&p2, 1., 2.);
v1.Vector2_init(&v1, 1., 1.);
v2.Vector2_init(&v2, 2., 4.);
// Expected status: PARALLEL_NON_INTERSECTING

p1.Point2_init_with_xy(&p1, 0., 0.);
p2.Point2_init_with_xy(&p2, 1., -1.);
v1.Vector2_init(&v1, 2., 0.);
v2.Vector2_init(&v2, 0., 3.);
// Expected intersection point: (1,0)
// Expected status: POINT

p1.Point2_init_with_xy(&p1, 0., 0.);
p2.Point2_init_with_xy(&p2, 1., 0.);
v1.Vector2_init(&v1, 2., 0.);
v2.Vector2_init(&v2, 2., 0.);
// Expected status: COLINEAR_INTERSECTING

p1.Point2_init_with_xy(&p1, 0., 0.);
p2.Point2_init_with_xy(&p2, 2., 0.);
v1.Vector2_init(&v1, 1., 0.);
v2.Vector2_init(&v2, 1., 0.);
// Expected status: COLINEAR_NON_INTERSECTING

p1.Point2_init_with_xy(&p1, 0., 0.);
p2.Point2_init_with_xy(&p2, 2., 2.);
v1.Vector2_init(&v1, 1., 0.);
v2.Vector2_init(&v2, -1., 1.);
// Expected status: NON_INTERSECTING


#endif
int main() {
    Point2 p1, p2, intersection;
    Vector2 v1, v2;
    Segment2 s1, s2;


p1.Point2_init_with_xy(&p1, 0., 0.);
p2.Point2_init_with_xy(&p2, 2., 0.);
v1.Vector2_init(&v1, 1., 0.);
v2.Vector2_init(&v2, 1., 0.);
    
    s1.Segment2_init(&s1, p1, v1);
    s2.Segment2_init(&s2, p2, v2);

    std::cout << "Points 1 and 2 : \n";
    p2.Point2_print(&p2);
    p1.Point2_print(&p1);

    std::cout << "Vectors 1 and 2 :\n";
    v1.Vector2_print(&v1);
    v2.Vector2_print(&v2);

    std::cout << "\nSegments:\n";
    s1.Segment2_print(&s1);
    s2.Segment2_print(&s2);

    IntersectionStatus status = s1.Segment2_intersect(&s1, &s2, &intersection);

    std::cout << "\nIntersection status: "
              << Segment2_statusToString(status) << "\n";

    if (status == POINT) {
        std::cout << "Intersection point: ";
        intersection.Point2_print(&intersection);
    }


  return 0;
}