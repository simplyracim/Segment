#include <vector>
#include <string>
#include <sstream>

#include "Point.h"
#include "Vector.h"
#include "Segment.h"
#include "View.h"

int main() {
    std::vector<Segment> segments;

    // Create 10 segments
    segments.emplace_back(Point(0.f,   0.f),  Vector(1.f,  2.f));   // S0
    segments.emplace_back(Point(2.f,   0.f),  Vector(1.f,  2.f));   // S1
    segments.emplace_back(Point(1.f,   1.f),  Vector(-1.f, 0.f));   // S2
    segments.emplace_back(Point(-1.f, -1.f),  Vector(0.f,  2.f));   // S3
    segments.emplace_back(Point(-2.f,  2.f),  Vector(4.f, -1.f));   // S4
    segments.emplace_back(Point(3.f,  -1.f),  Vector(-2.f, 3.f));   // S5
    segments.emplace_back(Point(0.5f,  2.f),  Vector(1.f, -3.f));   // S6
    segments.emplace_back(Point(-3.f,  0.f),  Vector(6.f,  0.f));   // S7
    segments.emplace_back(Point(0.f,   3.f),  Vector(0.f, -4.f));   // S8
    segments.emplace_back(Point(1.f,  -2.f),  Vector(2.f,  1.f));   // S9

    // Log lines to show in the SFML "console"
    std::vector<std::string> logLines;

    // ==== Segment info ====
    logLines.push_back("==== All segments ====");
    for (std::size_t i = 0; i < segments.size(); ++i) {
        std::ostringstream oss;
        oss << "Segment " << i << ": ";

        // Very simple inline description instead of using print()
        const Point&  p = segments[i].origin;
        const Vector& v = segments[i].direction;

        oss << "origin = {" << p.getX() << " , " << p.getY() << "}, "
            << "dir = (" << v.getX() << ", " << v.getY() << ")";

        logLines.push_back(oss.str());
    }
    logLines.push_back("======================");

    // Compute intersections
    std::vector<Point> intersections;

    for (std::size_t i = 0; i < segments.size() - 1; ++i) {
        for (std::size_t j = i + 1; j < segments.size(); ++j) {

            Point intersection;
            IntersectionStatus status =
                segments[i].intersect(segments[j], intersection);

            // One line for the status
            {
                std::ostringstream oss;
                oss << "Segments " << i << " and " << j
                    << " -> " << Segment2_statusToString(status);
                logLines.push_back(oss.str());
            }

            // Extra line if they intersect in a point
            if (status == POINT) {
                std::ostringstream ossPt;
                ossPt << "  Intersection at {"
                      << intersection.getX() << " , "
                      << intersection.getY() << "}";
                logLines.push_back(ossPt.str());

                intersections.push_back(intersection);
            }
        }

        logLines.push_back("=============");
    }

    // Launch the view, passing the log lines too
    View view(segments, &intersections, logLines);
    view.run();

    return 0;
}
