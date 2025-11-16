#include <vector>
#include <iostream>

#include "Point.h"
#include "Vector.h"
#include "Segment.h"
#include "View.h"

int main() {
    std::vector<Segment> segments;

    // Create 10 segments (for example)
    segments.emplace_back(Point(0.f,   0.f),  Vector(1.f,  2.f));   // S0
    segments.emplace_back(Point(2.f,   0.f),  Vector(1.f,  2.f));   // S1
    segments.emplace_back(Point(1.f,   1.f),  Vector(-1.f, 0.f));   // S2
    segments.emplace_back(Point(-1.f, -1.f), Vector(0.f,  2.f));    // S3
    segments.emplace_back(Point(-2.f,  2.f), Vector(4.f, -1.f));    // S4
    segments.emplace_back(Point(3.f,  -1.f), Vector(-2.f, 3.f));    // S5
    segments.emplace_back(Point(0.5f,  2.f), Vector(1.f, -3.f));    // S6
    segments.emplace_back(Point(-3.f,  0.f), Vector(6.f,  0.f));    // S7
    segments.emplace_back(Point(0.f,   3.f), Vector(0.f, -4.f));    // S8
    segments.emplace_back(Point(1.f,  -2.f), Vector(2.f,  1.f));    // S9

    // Print them
    std::cout << "==== All segments ====\n";
    for (std::size_t i = 0; i < segments.size(); ++i) {
        std::cout << "Segment " << i << ":\n";
        segments[i].print();
    }
    std::cout << "======================\n\n";

    // Compute intersections
    std::vector<Point> intersections;

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
                intersections.push_back(intersection);
            }
        }
    }

    // Launch the view
    View view(segments, &intersections);
    view.run();

    return 0;
}