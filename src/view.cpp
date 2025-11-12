#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Vector.h"
#include "Segment.h"

// Convert your types to SFML
static sf::Vector2f toSF(Point p) { return sf::Vector2f(p.getX(), p.getY()); }
static sf::Vector2f toSF(Vector v) { return sf::Vector2f(v.getX(), v.getY()); }

// Draw a filled circle at a position
static void drawPoint(sf::RenderWindow& window, const sf::Vector2f& pos, float radius, sf::Color color) {
    sf::CircleShape c(radius);
    c.setFillColor(color);
    c.setOrigin(sf::Vector2f{radius, radius});  // center the circle (SFML 3)
    c.setPosition(pos);
    window.draw(c);
}

// Draw a line segment from A to B
static void drawSegment(sf::RenderWindow& window, const sf::Vector2f& A, const sf::Vector2f& B, sf::Color color) {
    sf::Vertex line[2];
    line[0].position = A;
    line[0].color    = color;
    line[1].position = B;
    line[1].color    = color;

    window.draw(line, 2, sf::PrimitiveType::Lines);  // SFML 3 enum
}

void drawScene(const Segment& s1, const Segment& s2, const Point* intersectionOpt) {
    const unsigned W = 800, H = 600;
    sf::RenderWindow window(sf::VideoMode({W, H}), "Segment demo");  // SFML 3

    // Simple world-to-screen transform
    const float scale = 80.0f;
    const sf::Vector2f center(W/2.f, H/2.f);
    auto worldToScreen = [&](sf::Vector2f v) {
        v.x =  v.x * scale + center.x;
        v.y = -v.y * scale + center.y; // flip Y
        return v;
    };

    // Build endpoints from your representation: P, P+dir
    Point P1 = s1.origin, P2 = s2.origin;
    Vector D1 = s1.direction, D2 = s2.direction;

    Point Q1 = translate(P1, D1);
    Point Q2 = translate(P2, D2);

    auto P1s = worldToScreen(toSF(P1));
    auto Q1s = worldToScreen(toSF(Q1));
    auto P2s = worldToScreen(toSF(P2));
    auto Q2s = worldToScreen(toSF(Q2));

    sf::Color colA(80, 180, 255);
    sf::Color colB(255, 120, 80);
    sf::Color colPt(30, 220, 120);

    while (window.isOpen()) {
        while (auto e = window.pollEvent()) {       // SFML 3: optional<Event>
            if (e->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear(sf::Color(25, 25, 28));

        // Axes (optional)
        drawSegment(window, worldToScreen({-5.f, 0.f}), worldToScreen({ 5.f, 0.f}), sf::Color(70,70,70));
        drawSegment(window, worldToScreen({ 0.f,-4.f}), worldToScreen({ 0.f, 4.f}), sf::Color(70,70,70));

        // Draw segments
        drawSegment(window, P1s, Q1s, colA);
        drawSegment(window, P2s, Q2s, colB);

        // Draw endpoints
        drawPoint(window, P1s, 5.f, colA);
        drawPoint(window, Q1s, 5.f, colA);
        drawPoint(window, P2s, 5.f, colB);
        drawPoint(window, Q2s, 5.f, colB);

        // Intersection (if provided)
        if (intersectionOpt) {
            auto Is = worldToScreen(toSF(*intersectionOpt));
            drawPoint(window, Is, 6.f, colPt);
        }

        window.display();
    }
}
