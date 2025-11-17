#include "View.h"

void View::handleResize(unsigned newW, unsigned newH)
{
    // Recenter view — scaling stays the same.
    m_center = { newW / 2.f, newH / 2.f };

    // Update the SFML internal view to match new window size
    sf::View view = m_window.getView();
    view.setSize({ static_cast<float>(newW),
                   static_cast<float>(newH) });
    view.setCenter(m_center);
    m_window.setView(view);
}

void View::handleEvents()
{
    while (auto e = m_window.pollEvent()) {
        if (e->is<sf::Event::Closed>()) {
            m_window.close();
        }

        // Handle resize: keep fixed world scale, just recenter
        if (auto* r = e->getIf<sf::Event::Resized>()) {
            handleResize(r->size.x, r->size.y);
        }

        // Mouse wheel: zoom / pan
        if (auto* mw = e->getIf<sf::Event::MouseWheelScrolled>()) {
            handleMouseWheel(*mw);
        }
    }
}

void View::handleMouseWheel(const sf::Event::MouseWheelScrolled& wheel)
{
    // Modifier keys
    bool ctrl  = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LControl) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::RControl);
    bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::LShift) ||
                 sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::RShift);

    float delta = wheel.delta;          // >0 = scroll up, <0 = scroll down

    const float panSpeed  = 30.f;       // pixels per wheel tick
    const float zoomStep  = 1.3f;       // zoom factor per tick

    if (ctrl) {
        // ========= ZOOM (Ctrl + scroll, around mouse) =========
        float factor = (delta > 0.f) ? zoomStep : (1.f / zoomStep);

        float oldScale = m_scale;
        float newScale = oldScale * factor;

        /*
        // Clamp zoom
        const float minScale = 1.f;
        const float maxScale = 4000.f;
        if (newScale < minScale) newScale = minScale;
        if (newScale > maxScale) newScale = maxScale;
        */

        if (newScale == oldScale)
            return; // nothing to do (hit clamp)

        // Screen position of mouse (in pixels, relative to window)
        sf::Vector2f S{
            static_cast<float>(wheel.position.x),
            static_cast<float>(wheel.position.y)
        };

        // Adjust center so the world point under the mouse stays fixed
        float k = newScale / oldScale;

        // c' = S * (1 - k) + c * k
        m_center = {
            S.x * (1.f - k) + m_center.x * k,
            S.y * (1.f - k) + m_center.y * k
        };

        m_scale = newScale;
    } else {
        // ========= PANNING =========
        float amount = panSpeed * delta;

        if (shift) {
            // Horizontal pan (Shift + scroll)
            m_center.x += amount;
        } else {
            // Vertical pan (plain scroll)
            m_center.y += amount;
        }
    }
}
