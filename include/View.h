#ifndef VIEW_H
#define VIEW_H

#include "Segment.h"

#include <vector>
#include <SFML/Graphics.hpp>

class Segment;
class Point;

class View {
public:
    View(const std::vector<Segment>& segments,
         const std::vector<Point>* intersectionsOpt = nullptr,
         const std::vector<std::string>& logLines = {});  // <-- new param

    void run();

private:
    const std::vector<Segment>& m_segments;
    const std::vector<Point>*   m_intersections;

    sf::RenderWindow m_window;
    float            m_scale;
    sf::Vector2f     m_center;

    std::vector<sf::Color>      m_segColors;
    sf::Font                    m_font;
    bool                        m_fontLoaded;

    // NEW: log content
    std::vector<std::string>    m_logLines;

    sf::Vector2f worldToScreen(sf::Vector2f v) const;

    void handleEvents();
    void handleResize(unsigned newWidth, unsigned newHeight);
    void handleMouseWheel(const sf::Event::MouseWheelScrolled& wheel);

    void drawAxes();
    void drawAxisLabels();
    void drawSegments();
    void drawIntersections();
    void drawConsole();   // <--- new
};

#endif // VIEW_H