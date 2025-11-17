#include "View.h"

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

// ======= Drawing methods =======

void View::drawAxes()
{
    // ----- Grid (sub-axes) -----
    const int gridMax = 10;
    sf::Color gridColor(40, 40, 40);

    // vertical
    for (int x = -gridMax; x <= gridMax; ++x) {
        if (x == 0) continue;

        sf::Vector2f a = worldToScreen({ static_cast<float>(x), -static_cast<float>(gridMax) });
        sf::Vector2f b = worldToScreen({ static_cast<float>(x),  static_cast<float>(gridMax)  });
        drawSegment(m_window, a, b, gridColor);
    }

    // horizontal
    for (int y = -gridMax; y <= gridMax; ++y) {
        if (y == 0) continue;

        sf::Vector2f a = worldToScreen({ -static_cast<float>(gridMax), static_cast<float>(y) });
        sf::Vector2f b = worldToScreen({  static_cast<float>(gridMax), static_cast<float>(y) });
        drawSegment(m_window, a, b, gridColor);
    }

    // ----- Main axes (X and Y) -----
    sf::Color axisColor(70, 70, 70);

    // X axis
    drawSegment(m_window,
                worldToScreen({ -50.f, 0.f }),
                worldToScreen({  50.f, 0.f }),
                axisColor);

    // Y axis
    drawSegment(m_window,
                worldToScreen({ 0.f, -50.f }),
                worldToScreen({ 0.f,  50.f }),
                axisColor);
}

void View::drawAxisLabels()
{
    if (!m_fontLoaded) return;

    const int maxX = 10;
    const int maxY = 10;

    // ---------- X-axis labels ----------
    for (int x = -maxX; x <= maxX; ++x) {
        if (x == 0) continue;

        sf::Text text(m_font, std::to_string(x));
        text.setCharacterSize(14);
        text.setFillColor(sf::Color(180, 180, 180));

        sf::Vector2f worldPos(static_cast<float>(x), -0.2f);
        sf::Vector2f screenPos = worldToScreen(worldPos);

        sf::FloatRect bounds = text.getLocalBounds();
        float w = bounds.size.x;

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

        sf::Vector2f worldPos(0.2f, static_cast<float>(y));
        sf::Vector2f screenPos = worldToScreen(worldPos);

        sf::FloatRect bounds = text.getLocalBounds();
        float w = bounds.size.x;
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

    sf::Color outlineColor(70, 70, 70);

    for (const auto& inter : *m_intersections) {
        auto Is = worldToScreen(toSF(inter));

        sf::CircleShape c(6.f);
        c.setFillColor(sf::Color::Transparent);
        c.setOutlineColor(outlineColor);
        c.setOutlineThickness(2.f);
        c.setOrigin({6.f, 6.f});
        c.setPosition(Is);

        m_window.draw(c);
    }
}
