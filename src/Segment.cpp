#include "Segment.h"
#include <cmath>

const char* Segment2_statusToString(IntersectionStatus status) {
    switch (status) {
        case POINT:                     return "POINT : ";
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

Point Segment::getOrigin() const {
    return this->origin;
}

Vector Segment::getDirection() const {
    return this->direction;
}

float Segment::length() const {
    return direction.length();
}
IntersectionStatus Segment::intersect(const Segment& other, Point& p) const {
    const float EPS = 1e-6f;

    Point  oa = getOrigin();
    Point  ob = other.getOrigin();
    Vector da = getDirection();
    Vector db = other.getDirection();

    Vector dc = vector_from_points(ob, oa);

    float det = da.cross(db);

    // ---- Case 1: not parallel (unique intersection of infinite lines) ----
    if (std::fabs(det) > EPS) {
        float u = dc.cross(db) / det;
        float v = dc.cross(da) / det;

        // intersection lies on both segments
        if (u >= 0.0f && u <= 1.0f &&
            v >= 0.0f && v <= 1.0f) {

            Vector tmp = da.dot_scalar(u);
            p = translate(oa, tmp);
            return POINT;
        }

        // lines intersect, but segments don't
        return NON_INTERSECTING;
    }

    // ---- Case 2: parallel or collinear ----
    float st = dc.cross(da);

    // parallel but not collinear
    if (std::fabs(st) > EPS) {
        return PARALLEL_NON_INTERSECTING;
    }

    // ---- Case 3: collinear ----
    float pj = da.dot(da);

    // subcase: segB is degenerate (a point)
    if (pj <= EPS) {
        float pj_r = db.dot(db);

        if (pj_r <= EPS) {
            // both are points
            Vector oo = vector_from_points(ob, oa);
            if (std::fabs(oo.getX()) <= EPS &&
                std::fabs(oo.getY()) <= EPS) {
                p = oa;
                return COLINEAR_INTERSECTING;
            }
            return COLINEAR_NON_INTERSECTING;
        } else {
            // check if oa lies on this segment
            Vector ob_oa = vector_from_points(oa, ob); // oa - ob
            float t = ob_oa.dot(db) / pj_r;
            if (t >= -EPS && t <= 1.0f + EPS) {
                p = oa;
                return COLINEAR_INTERSECTING;
            }
            return COLINEAR_NON_INTERSECTING;
        }
    }

    // subcase: non-degenerate collinear segments
    float d1 = dc.dot(da) / pj;          // parameter for ob
    float d2 = d1 + db.dot(da) / pj;     // parameter for ob + db

    // normalize order
    if (d1 > d2) {
        float tmp = d1;
        d1 = d2;
        d2 = tmp;
    }

    float lo = std::fmax(0.0f, d1);
    float hi = std::fmin(1.0f, d2);

    if (hi >= lo - EPS) {
        // overlap exists → return midpoint on segB
        float t = 0.5f * (lo + hi);
        Vector step = da.dot_scalar(t);
        p = translate(oa, step);
        return COLINEAR_INTERSECTING;
    }

    return COLINEAR_NON_INTERSECTING;
}

void Segment::print() const {
    std::cout << "Segment:\n";

    std::cout << "  Origin: ";
    this->origin.print();

    std::cout << "  Direction: ";
    this->direction.print();

    std::cout << "  Length: " << direction.length() << "\n\n";
}