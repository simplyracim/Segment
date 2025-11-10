#include "Segment2.h"

const char* Segment2_statusToString(IntersectionStatus status) {
    switch (status) {
        case POINT:                     return "POINT (Segments intersect at one point)";
        case COLINEAR_INTERSECTING:     return "COLINEAR_INTERSECTING (Overlapping)";
        case COLINEAR_NON_INTERSECTING: return "COLINEAR_NON_INTERSECTING (Same line but disjoint)";
        case PARALLEL_NON_INTERSECTING: return "PARALLEL_NON_INTERSECTING";
        case NON_INTERSECTING:          return "NON_INTERSECTING";
        default:                        return "UNKNOWN";
    }
}

void Segment2::Segment2_init(Segment2 *s, Point2 origin, Vector direction) {
    s->origin = origin;
    s->direction = direction;
}

Point2 Segment2::Segment2_getOrigin(const Segment2 *s) {
    return s->origin;
}

Vector Segment2::Segment2_getDirection(const Segment2 *s) {
    return s->direction;
}

float Segment2::Segment2_length(const Segment2 *s) {
    // return direction.Vector_norm(&s->direction);
    return s->direction.norm(); // CHANGED: use Vector::norm()
}

IntersectionStatus Segment2::Segment2_intersect(const Segment2 *s, const Segment2 *r, Point2 *p) {
    Point2 oa = Segment2_getOrigin(s), ob = Segment2_getOrigin(r);
    Vector da = Segment2_getDirection(s), db = Segment2_getDirection(r);
    Vector dc = Point2_sub(&ob, &oa);

    IntersectionStatus status;
    // float det = direction.Vector_cross(&da, &db);
    float det = da.cross(db); // CHANGED: use Vector::cross()

    if (det != 0.0) {
        float u, v;

        // u = direction.Vector_cross(&dc, &db) / det;
        // v = direction.Vector_cross(&dc, &da) / det;
        u = dc.cross(db) / det; // CHANGED
        v = dc.cross(da) / det; // CHANGED

        if ((u >= 0.0 && u <= 1.0) && (v >= 0.0 && v <= 1.0)) {
            // Vector tmp = direction.Vector_dot_scalar(&da, u);
            Vector tmp = da.dot_scalar(u); // CHANGED: use Vector::dot_scalar()
            *p = Point2_add(&oa, &tmp);
            status = POINT;
        } else {
            status = NON_INTERSECTING;
        }
    } else {
        // float st = direction.Vector_cross(&dc, &da);
        float st = dc.cross(da); // CHANGED: use Vector::cross()

        if (det == 0.0 && st == 0.0) { // check for collinearity
            float pj, d1, d2;

            // pj = direction.Vector_dot(&da, &da);
            pj = da.dot(da); // CHANGED: use Vector::dot()
            // d1 = direction.Vector_dot(&dc, &da) / pj;
            // d2 = d1 + direction.Vector_dot(&db, &da) / pj;
            d1 = dc.dot(da) / pj;         // CHANGED
            d2 = d1 + db.dot(da) / pj;    // CHANGED

            if (d1 >= 0.0 && d1 <= 1.0) {
                *p = ob;
                status = COLINEAR_INTERSECTING;
            } else if (d2 >= 0.0 && d2 <= 1.0) {
                Point2 tmp_ob_db = Point2_add(&ob, &db);
                *p = tmp_ob_db;
                status = COLINEAR_INTERSECTING;
            } else {
                status = COLINEAR_NON_INTERSECTING;
            }
        } else if (det == 0.0 && st != 0.0) {
            status = PARALLEL_NON_INTERSECTING;
        }
    }

    return status;
}

void Segment2::Segment2_print(Segment2 *s) {
    std::cout << "Segment:\n";
    std::cout << "  Origin: ";
    s->origin.Point2_print(&s->origin);
    std::cout << "  Direction: ";
    // s->direction.Vector_print(&s->direction);
    s->direction.print(); // CHANGED: use Vector::print()
    // std::cout << "  Length: " << s->direction.Vector_norm(&s->direction) << "\n\n";
    std::cout << "  Length: " << s->direction.norm() << "\n\n"; // CHANGED: use Vector::norm()
}
