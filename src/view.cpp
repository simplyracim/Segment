#include "View.h"
#include "Point.h"
#include "Vector.h"
#include "Segment.h"

#include <random>

// ======= Small free helpers (file-local) =======

static sf::Vector2f toSF(const Point& p)  { return { p.getX(), p.getY() }; }
static sf::Vector2f toSF(const Vector& v) { return { v.getX(), v.getY() }; }

static void drawPoint(sf::RenderWindow& window,
                      const sf::Vector2f& pos,
                      float radius,
                      sf::Color color)
{
    sf::CircleShape c(radius);
    c.setFillColor(color);
    c.setOrigin({radius, radius});
    c.setPosition(pos);
    window.draw(c);
}

static void drawSegment(sf::RenderWindow& window,
                        const sf::Vector2f& A,
                        const sf::Vector2f& B,
                        sf::Color color)
{
    sf::Vertex line[2];
    line[0].position = A;
    line[0].color    = color;
    line[1].position = B;
    line[1].color    = color;

    window.draw(line, 2, sf::PrimitiveType::Lines);
}

// ======= View methods =======

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
    std::uniform_int_distribution<int> dist(0, 30);

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

void View::handleEvents()
{
    while (auto e = m_window.pollEvent()) {  // SFML 3 optional<Event>
        if (e->is<sf::Event::Closed>()) {
            m_window.close();
        }
    }
}

void View::drawAxes()
{
    drawSegment(m_window,
                worldToScreen({-5.f, 0.f}),
                worldToScreen({ 5.f, 0.f}),
                sf::Color(70,70,70));

    drawSegment(m_window,
                worldToScreen({ 0.f,-4.f}),
                worldToScreen({ 0.f, 4.f}),
                sf::Color(70,70,70));
}

void View::drawAxisLabels()
{
    if (!m_fontLoaded) return;

    const int maxX = 5;
    const int maxY = 4;

    // ---------- X-axis labels ----------
    for (int x = -maxX; x <= maxX; ++x) {
        if (x == 0) continue;

        sf::Text text(m_font, std::to_string(x));
        text.setCharacterSize(14);
        text.setFillColor(sf::Color(180, 180, 180));

        sf::Vector2f worldPos((float)x, -0.2f);
        sf::Vector2f screenPos = worldToScreen(worldPos);

        sf::FloatRect bounds = text.getLocalBounds();
        float w = bounds.size.x;   // <-- FIXED
        float h = bounds.size.y;

        text.setOrigin({ w / 2.f, 0.f });
        text.setPosition(screenPos);

        m_window.draw(text);
    }

    // ---------- Y-axis labels ----------
    for (int y = -maxY; y <= maxY; ++y) {
        if (y == 0) continue;

        sf::Text text(m_font, std::to_string(y));
        text.setCharacterSize(14);
        text.setFillColor(sf::Color(180, 180, 180));

        sf::Vector2f worldPos(0.2f, (float)y);
        sf::Vector2f screenPos = worldToScreen(worldPos);

        sf::FloatRect bounds = text.getLocalBounds();
        float w = bounds.size.x;   // <-- FIXED
        float h = bounds.size.y;

        text.setOrigin({ w + 4.f, h / 2.f });
        text.setPosition(screenPos);

        m_window.draw(text);
    }
}

void View::drawSegments()
{
    for (std::size_t i = 0; i < m_segments.size(); ++i) {
        const Segment& s     = m_segments[i];
        const sf::Color& col = m_segColors[i];

        Point  P = s.origin;
        Vector D = s.direction;
        Point  Q = translate(P, D);   // endpoint = origin + direction

        auto Ps = worldToScreen(toSF(P));
        auto Qs = worldToScreen(toSF(Q));

        drawSegment(m_window, Ps, Qs, col);
        drawPoint(m_window, Ps, 3.f, col);
        drawPoint(m_window, Qs, 3.f, col);
    }
}

void View::drawIntersections()
{
    if (!m_intersections) return;

    sf::Color outlineColor(70, 70, 70); // bright green outline

    for (const auto& inter : *m_intersections) {
        auto Is = worldToScreen(toSF(inter));

        sf::CircleShape c(6.f);                 // radius = 6
        c.setFillColor(sf::Color::Transparent); // no fill
        c.setOutlineColor(outlineColor);        // outline color
        c.setOutlineThickness(2.f);             // thickness of outline
        c.setOrigin({6.f, 6.f});                // center the circle
        c.setPosition(Is);

        m_window.draw(c);
    }
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
