#ifndef SEGMENTMANAGER_H
#define SEGMENTMANAGER_H

#include "Segment.h"
#include <vector>

class GestionSegments {
private:
    std::vector<Segment> segments;

public:
    void ajouterSegment(const Segment& s) {
        segments.push_back(s);
    }

    void afficherSegments() {
        for (const auto& s : segments) {
            s.print();
        }
    }

    void afficherIntersections() {
        for (int i = 0; i < (int)segments.size(); ++i) {
            for (int j = i+1; j < (int)segments.size(); ++j) {
                Point inter;
                IntersectionStatus st = segments[i].intersect(segments[j], inter);
                // print status, maybe intersection point
            }
        }
    }
};

#endif // SEGMENTMANAGER_H