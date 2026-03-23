// ==============================================================================
// Includes
// ------------------------------------------------------------------------------

#include "camera.h"

// ==============================================================================
// Class Camera
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
Camera& Camera::get_instance(sf::RenderWindow& window) {

    static Camera instance(window);
    return instance;
}

// ------------------------------------------------------------------------------
void Camera::update_camera(std::optional<sf::Event> const& event) {

    // Check for an event
    if (auto const e = event->getIf<sf::Event::MouseWheelScrolled>()) {

        _event__mouse_wheel_scrolled(e);
    }

    // Set window to use view
    _window.setView(_view);
}

// ------------------------------------------------------------------------------
Camera::Camera(sf::RenderWindow& window)
    : _window(window)
    , _view()
    {

    // Initialize view
    _view.setCenter(_get_win_center());
    _view.setSize  (_get_win_size  ());
}

// ------------------------------------------------------------------------------
sf::Vector2f Camera::_get_win_size() const {

    sf::Vector2f const win_size = static_cast<sf::Vector2f>(_window.getSize());

    return win_size;
}

// ------------------------------------------------------------------------------
sf::Vector2f Camera::_get_win_center() const {

    sf::Vector2f const win_center = {
        _window.getSize().x / 2.0f,
        _window.getSize().y / 2.0f
        };

    return win_center;
}

// ------------------------------------------------------------------------------
sf::Vector2f Camera::_get_mouse_pos() const {

    // Get mouse pos in pixels
    sf::Vector2i const mouse_pos_px = sf::Mouse::getPosition(_window);

    // Convert to world co-ordinates
    sf::Vector2f const mouse_pos_world_coords = _window.mapPixelToCoords(mouse_pos_px);

    return mouse_pos_world_coords;
}

// ------------------------------------------------------------------------------
void Camera::_event__mouse_wheel_scrolled(sf::Event::MouseWheelScrolled const* e) {

    // Get delta from scroll event
    float const delta = e->delta;

    // Each scroll zooms either 10% in or 10% out
    float const zoom_step = 0.1f;

    // Factor to zoom in or out by
    float const zoom_factor = (delta > 0.0f) ? (1.0f - zoom_step) : (1.0f + zoom_step);

    // Shift view center toward mouse so the point under the cursor stays fixed
    sf::Vector2f const mouse  = _get_mouse_pos();
    sf::Vector2f const center = _view.getCenter();
    sf::Vector2f const offset = (mouse - center) * (1.0f - zoom_factor);

    // Zoom where the mouse is depending on factor
    _view.zoom(zoom_factor);
    _view.move(offset);
}
