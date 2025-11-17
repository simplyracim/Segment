#include "View.h"

#include <random>

// ======= View core (ctor, helpers, main loop) =======

View::View(const std::vector<Segment>& segments,
           const std::vector<Point>* intersectionsOpt)
    : m_segments(segments)
    , m_intersections(intersectionsOpt)
    , m_window(sf::VideoMode({800u, 600u}), "Segment demo")
    , m_scale(80.f)
    , m_center(800.f / 2.f, 600.f / 2.f)
    , m_fontLoaded(false)
{
    // Load font (adjust path to where your .ttf file is)
    m_fontLoaded = m_font.openFromFile("assets/consolas-regular.ttf");

    // Random color generator (stable per View instance)
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 255);

    m_segColors.reserve(m_segments.size());
    for (std::size_t i = 0; i < m_segments.size(); ++i) {
        m_segColors.emplace_back(
            sf::Color(
                80  + dist(rng),
                180 + dist(rng),
                255 - dist(rng)
            )
        );
    }
}

sf::Vector2f View::worldToScreen(sf::Vector2f v) const
{
    v.x =  v.x * m_scale + m_center.x;
    v.y = -v.y * m_scale + m_center.y; // flip Y
    return v;
}

void View::run()
{
    while (m_window.isOpen()) {
        handleEvents();
        m_window.clear(sf::Color(25, 25, 28));

        drawAxes();
        drawSegments();
        drawIntersections();
        drawAxisLabels();

        m_window.display();
    }
}
