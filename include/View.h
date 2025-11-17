#ifndef VIEW_H
#define VIEW_H

#include <vector>
#include <SFML/Graphics.hpp>

class Segment;
class Point;

class View {
public:
    View(const std::vector<Segment>& segments,
         const std::vector<Point>* intersectionsOpt = nullptr);

    void run();

private:
    // references to your data (not owned)
    const std::vector<Segment>& m_segments;
    const std::vector<Point>*   m_intersections;

    // SFML state
    sf::RenderWindow m_window;
    float            m_scale;
    sf::Vector2f     m_center;

    // one color per segment
    std::vector<sf::Color> m_segColors;

    sf::Font m_font;
    bool     m_fontLoaded;

    // helpers
    sf::Vector2f worldToScreen(sf::Vector2f v) const;

    void handleEvents();
    void handleResize(unsigned newWidth, unsigned newHeight);
    void handleMouseWheel(const sf::Event::MouseWheelScrolled& wheel);
    void drawAxes();
    void drawSegments();
    void drawIntersections();
    void drawAxisLabels();
};

#endif // VIEW_H