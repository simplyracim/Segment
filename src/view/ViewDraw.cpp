#include "View.h"

#include <sstream>
#include <iomanip>
#include <cmath>

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

static float computeGridStep(float scale)
{
    const float targetPixels = 500.f;

    // Approximate the desired spacing in world units
    float rawStep = targetPixels / scale;

    if (rawStep <= 0.f)
        return 1.f;

    // Compute k such that step = 10^k is closest to rawStep
    float exponent = std::round(std::log2(rawStep));

    // Return 10^k
    return std::pow(2.f, exponent);
}

static std::string formatNumber(float value, float step)
{
    // Treat tiny values as zero to avoid "-0.0"
    if (std::fabs(value) < 1e-6f) {
        value = 0.f;
    }

    // Decide decimals based on powers-of-two step
    int decimals = 0;
    float s = step;

    // Cap at 6 decimals so it doesn't go crazy
    while (s < 1.f && decimals < 6) {
        s *= 2.f;      // because your grid uses 2^k steps
        ++decimals;
    }

    // Round to that many decimals
    float pow10 = 1.f;
    for (int i = 0; i < decimals; ++i) {
        pow10 *= 10.f;
    }

    float rounded = std::round(value * pow10) / pow10;

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(decimals) << rounded;
    std::string str = oss.str();

    // Only strip trailing zeros in the fractional part
    auto dotPos = str.find('.');
    if (dotPos != std::string::npos) {
        // strip zeros to the right of the dot
        while (str.size() > dotPos + 1 && str.back() == '0') {
            str.pop_back();
        }
        // if we end up with a trailing dot, remove it
        if (!str.empty() && str.back() == '.') {
            str.pop_back();
        }
    }

    if (str.empty()) {
        str = "0";
    }

    return str;
}

// ======= Drawing methods =======

void View::drawAxes()
{
    sf::Vector2u size = m_window.getSize();

    // Visible world range
    float worldLeft   = (0.f          - m_center.x) / m_scale;
    float worldRight  = (size.x * 1.f - m_center.x) / m_scale;
    float worldTop    = (m_center.y - 0.f)          / m_scale;
    float worldBottom = (m_center.y - size.y * 1.f) / m_scale;

    // Base grid spacing in world units
    float baseStep = computeGridStep(m_scale * 2);
    float fineStep = baseStep / 10.f;
    const float eps = 1e-6f;

    const int baseEvery   = 10;
    const int coarseEvery = 20;

    // We'll draw lines at x = n * fineStep
    int nXStart = static_cast<int>(std::floor(worldLeft  / fineStep));
    int nXEnd   = static_cast<int>(std::ceil (worldRight / fineStep));
    int nYStart = static_cast<int>(std::floor(worldBottom / fineStep));
    int nYEnd   = static_cast<int>(std::ceil (worldTop    / fineStep));

    // Colors for different magnitudes
    sf::Color colFine   (35, 35, 35);   // weakest
    sf::Color colBase   (50, 50, 50);   // medium
    sf::Color colCoarse (70, 70, 70);   // strongest (still below axis)
    sf::Color axisColor (100, 100, 100);

    // ---------- Vertical grid lines ----------
    for (int n = nXStart; n <= nXEnd; ++n) {
        float x = n * fineStep;

        // Skip main Y axis; we'll draw it separately
        if (std::fabs(x) < eps)
            continue;

        bool isBase   = (n % baseEvery   == 0);
        bool isCoarse = (n % coarseEvery == 0);

        sf::Color col = colFine;
        if (isBase)   col = colBase;
        if (isCoarse) col = colCoarse;

        sf::Vector2f a = worldToScreen({ x, worldBottom });
        sf::Vector2f b = worldToScreen({ x, worldTop    });
        drawSegment(m_window, a, b, col);
    }

    // ---------- Horizontal grid lines ----------
    for (int n = nYStart; n <= nYEnd; ++n) {
        float y = n * fineStep;

        // Skip main X axis
        if (std::fabs(y) < eps)
            continue;

        bool isBase   = (n % baseEvery   == 0);
        bool isCoarse = (n % coarseEvery == 0);

        sf::Color col = colFine;
        if (isBase)   col = colBase;
        if (isCoarse) col = colCoarse;

        sf::Vector2f a = worldToScreen({ worldLeft,  y });
        sf::Vector2f b = worldToScreen({ worldRight, y });
        drawSegment(m_window, a, b, col);
    }

    // ---------- Main axes (strongest) ----------
    // X axis: y = 0
    drawSegment(m_window,
                worldToScreen({ worldLeft,  0.f }),
                worldToScreen({ worldRight, 0.f }),
                axisColor);

    // Y axis: x = 0
    drawSegment(m_window,
                worldToScreen({ 0.f, worldBottom }),
                worldToScreen({ 0.f, worldTop    }),
                axisColor);
}

void View::drawAxisLabels()
{
    if (!m_fontLoaded) return;

    sf::Vector2u size = m_window.getSize();

    float worldLeft   = (0.f          - m_center.x) / m_scale;
    float worldRight  = (size.x * 1.f - m_center.x) / m_scale;
    float worldTop    = (m_center.y - 0.f)          / m_scale;
    float worldBottom = (m_center.y - size.y * 1.f) / m_scale;

    // Same step logic as drawAxes()
    float step = computeGridStep(m_scale);
    float fineStep = step / 10;
    const float eps = 1e-6f;

    // Index ranges in fine-step space
    int nXStart = static_cast<int>(std::floor(worldLeft   / fineStep));
    int nXEnd   = static_cast<int>(std::ceil (worldRight  / fineStep));
    int nYStart = static_cast<int>(std::floor(worldBottom / fineStep));
    int nYEnd   = static_cast<int>(std::ceil (worldTop    / fineStep));

    const float labelOffsetX = -0.2f / m_scale;  // below X axis in world coords
    const float labelOffsetY =  0.2f / m_scale;  // right of Y axis

    // ---------- X-axis labels (for vertical lines) ----------
    for (int n = nXStart; n <= nXEnd; ++n) {
        float x = n * fineStep;

        // skip main Y axis
        if (std::fabs(x) < eps)
            continue;

        sf::Text text(m_font, formatNumber(x, fineStep));
        text.setCharacterSize(14);
        text.setFillColor(sf::Color(180, 180, 180));

        sf::Vector2f worldPos(x, labelOffsetX);
        sf::Vector2f screenPos = worldToScreen(worldPos);

        sf::FloatRect bounds = text.getLocalBounds();
        float w = bounds.size.x;

        text.setOrigin({ w / 2.f, 0.f });
        text.setPosition(screenPos);

        m_window.draw(text);
    }

    // ---------- Y-axis labels (for horizontal lines) ----------
    for (int n = nYStart; n <= nYEnd; ++n) {
        float y = n * fineStep;

        // skip main X axis
        if (std::fabs(y) < eps)
            continue;

        sf::Text text(m_font, formatNumber(y, fineStep));
        text.setCharacterSize(14);
        text.setFillColor(sf::Color(180, 180, 180));

        sf::Vector2f worldPos(labelOffsetY, y);
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
