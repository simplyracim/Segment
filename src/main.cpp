#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Point.h"
#include "Vector.h"
#include "Segment.h"

void drawScene(const Segment& s1, const Segment& s2, const Point* intersectionOpt);

int main() {
    // 1) Build a list of segments
    std::vector<Segment> segments;

    // You can add as many as you like here:
    segments.emplace_back(Point(0.f, 0.f), Vector(1.f, 2.f));   // S0
    segments.emplace_back(Point(2.f, 0.f), Vector(1.f, 2.f));   // S1
    segments.emplace_back(Point(1.f, 1.f), Vector(-1.f, 0.f));  // S2
    segments.emplace_back(Point(-1.f, -1.f), Vector(0.f, 2.f)); // S3
    // etc...

    // 2) Print them all
    std::cout << "==== All segments ====\n";
    for (std::size_t i = 0; i < segments.size(); ++i) {
        std::cout << "Segment " << i << ":\n";
        segments[i].print();
    }

    std::cout << "======================\n\n";

    // 3) Compute intersections between ALL PAIRS (i, j) with i < j
    for (std::size_t i = 0; i < segments.size(); ++i) {
        for (std::size_t j = i + 1; j < segments.size(); ++j) {

            Point intersection;
            IntersectionStatus status =
                segments[i].intersect(segments[j], intersection);

            std::cout << "Segments " << i << " and " << j
                      << " -> " << Segment2_statusToString(status) << "\n";

            if (status == POINT) {
                std::cout << "  Intersection point: ";
                intersection.print();
            }
        }
    }

    // 4) Keep your old SFML visualization: show the first two segments
    if (segments.size() >= 2) {
        Point intersection;
        IntersectionStatus status =
            segments[0].intersect(segments[1], intersection);

        drawScene(segments[0],
                  segments[1],
                  (status == POINT ? &intersection : nullptr));
    }

    return 0;
}
