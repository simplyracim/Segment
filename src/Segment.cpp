#include "Segment.h"
#include <cmath>

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

Segment::Segment(Point origin, Vector direction) {
    this->origin = origin;
    this->direction = direction;
}

Point Segment::getOrigin() {
    return this->origin;
}

Vector Segment::getDirection() {
    return this->direction;
}

float Segment::length() {
    return direction.length();
}

IntersectionStatus Segment::intersect(Segment segA, Segment segB, Point p) {
    const float EPS = 1e-6f;

    Point oa = segA.getOrigin(), ob = segB.getOrigin();
    Vector da = segA.getDirection(), db = segB.getDirection();
    Vector dc = vector_from_points(ob, oa);

    IntersectionStatus status = NON_INTERSECTING;

    float det = da.cross(db);

    if (std::fabs(det) > EPS) {
        float u, v;

        u = dc.cross(db) / det; // CHANGED
        v = dc.cross(da) / det; // CHANGED

        if ((u >= 0.0f && u <= 1.0f) && (v >= 0.0f && v <= 1.0f)) {
            Vector tmp = da.dot_scalar(u); // CHANGED: use Vector::dot_scalar() as scale
            p = translate(oa, tmp);
            status = POINT;
        } else {
            status = NON_INTERSECTING;
        }
    } else {
        float st = dc.cross(da); // CHANGED: use Vector::cross()

        if (std::fabs(st) <= EPS) { // check for collinearity
            float pj = da.dot(da); // CHANGED: use Vector::dot()

            if (pj <= EPS) {
                // 's' is degenerate (a point). If that point lies on 'r', report it.
                // Project oa onto r's parameter; equivalently check perpendicular distance.
                float pj_r = db.dot(db);
                if (pj_r <= EPS) {
                    // both are points
                    Vector oo = vector_from_points(ob, oa);
                    if (std::fabs(oo.getX()) <= EPS && std::fabs(oo.getY()) <= EPS) {
                        p = oa;
                        status = COLINEAR_INTERSECTING;
                    } else {
                        status = COLINEAR_NON_INTERSECTING;
                    }
                } else {
                    // Check if oa is on r segment.
                    Vector ob_oa = vector_from_points(oa, ob); // oa - ob
                    float t = ob_oa.dot(db) / pj_r;
                    if (t >= -EPS && t <= 1.0f + EPS) {
                        p = oa;
                        status = COLINEAR_INTERSECTING;
                    } else {
                        status = COLINEAR_NON_INTERSECTING;
                    }
                }
            } else {
                // Parameters of r's endpoints on s
                float d1 = dc.dot(da) / pj;         // for ob
                float d2 = d1 + db.dot(da) / pj;    // for ob + db

                // normalize order
                if (d1 > d2) { float tmp = d1; d1 = d2; d2 = tmp; }

                float lo = std::fmax(0.0f, d1);
                float hi = std::fmin(1.0f, d2);

                if (hi >= lo - EPS) {
                    // They overlap. Return a representative point (midpoint of overlap on s).
                    float t = 0.5f * (lo + hi);
                    Vector step = da.dot_scalar(t);
                    p = translate(oa, step);
                    status = COLINEAR_INTERSECTING;
                } else {
                    status = COLINEAR_NON_INTERSECTING;
                }
            }
        } else {
            status = PARALLEL_NON_INTERSECTING;
        }
    }

    return status;
}

void Segment::print() {
    std::cout << "Segment:\n";

    std::cout << "  Origin: ";
    this->origin.print();

    std::cout << "  Direction: ";
    direction.print();

    std::cout << "  Length: " << direction.length() << "\n\n"; // CHANGED: use Vector::norm()
}