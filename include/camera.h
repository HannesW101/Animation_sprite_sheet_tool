// ==============================================================================
// Includes
// ------------------------------------------------------------------------------

#include "SFML/Graphics.hpp"

// ==============================================================================
// Class Camera
// ------------------------------------------------------------------------------

class Camera final {

public:
    // Get the singleton instance of the camera, needs
    // window to know where to apply the camera to.
    static Camera& get_instance(sf::RenderWindow& window);

    void update_camera(std::optional<sf::Event> const& event);

    // Delete copy and move
    Camera           (Camera const&) = delete;
    Camera& operator=(Camera const&) = delete;
    Camera           (Camera&&     ) = delete;
    Camera& operator=(Camera&&     ) = delete;

private:
    // Private singleton constructor
    Camera(sf::RenderWindow& window);

    // Default destructor
    ~Camera() = default;

    // Get the current window size
    sf::Vector2f _get_win_size() const;

    // Get the center point for the current window
    sf::Vector2f _get_win_center() const;

    // Get the current mouse position in world co-ordinates
    sf::Vector2f _get_mouse_pos() const;

    // Event for mouse wheel scroll: Zoom the view in or out
    void _event__mouse_wheel_scrolled(sf::Event::MouseWheelScrolled const* e);

    sf::RenderWindow& _window;
    sf::View          _view;
};
