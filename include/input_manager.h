// ==============================================================================
// Includes
// ------------------------------------------------------------------------------

#include "SFML/Graphics.hpp"

// ==============================================================================
// Class Input_manager
// ------------------------------------------------------------------------------

class Input_manager final {

public:
    // Get the singleton instance of the Input_manager, needs
    // window to know where to draw our objects to.
    static Input_manager& get_instance(sf::RenderWindow& window);

    // Handle all keyboard inputs
    void handle_inputs(std::optional<sf::Event> const& event);

    // Delete copy and move
    Input_manager           (Input_manager const&) = delete;
    Input_manager& operator=(Input_manager const&) = delete;
    Input_manager           (Input_manager&&     ) = delete;
    Input_manager& operator=(Input_manager&&     ) = delete;

private:
    // Private singleton constructor
    Input_manager(sf::RenderWindow& window);

    // Default destructor
    ~Input_manager() = default;

    // Handle various key pressed events
    void _key_pressed__d() const;
    void _key_pressed__a() const;
    void _key_pressed__w() const;
    void _key_pressed__s() const;
    void _key_pressed__right() const;
    void _key_pressed__left() const;
    void _key_pressed__up() const;
    void _key_pressed__down() const;
    void _key_pressed__shift_right() const;
    void _key_pressed__shift_left() const;
    void _key_pressed__shift_up() const;
    void _key_pressed__shift_down() const;
    void _key_pressed__enter() const;
    void _key_pressed__backspace() const;
    void _key_pressed__p() const;

    // Handle various mouse released events
    void _mouse_released__left() const;

    // Add all input controls to the overlay for user to see
    void _add_all_overlay_controls() const;

    sf::RenderWindow& _window;
};
