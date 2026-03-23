// ==============================================================================
// Includes
// ------------------------------------------------------------------------------

#include "SFML/Graphics.hpp"

#include <vector>

// ==============================================================================
// Class Object_manager
// ------------------------------------------------------------------------------

class Object_manager final {

public:
    // Get the singleton instance of the Object_manager, needs
    // window to know where to draw our objects to.
    static Object_manager& get_instance(sf::RenderWindow& window);

    // Can add a sprite sheet (only one can exist so it will
    // replace the current sprite sheet). Can add a
    // sf::RectangleShape by passing a sf::Vector2f indicating size.
    // Can add a sf::Text, by passing a string, to be displayed by the overlay
    void add_object(sf::Texture const& sprite_sheet);
    void add_object(sf::Vector2f const& size);
    void add_object(std::string const& text);

    // Draw the objects to the window
    void draw_objects();

    // Increase width of current rectangle by a certain amount
    void increase_width(float const delta);

    // Decrease width of current rectangle by a certain amount
    void decrease_width(float const delta);

    // Increase height of current rectangle by a certain amount
    void increase_height(float const delta);

    // Decrease height of current rectangle by a certain amount
    void decrease_height(float const delta);

    // Move current rectangle right
    void move_right(float const delta);

    // Move current rectangle left
    void move_left(float const delta);

    // Move current rectangle up
    void move_up(float const delta);

    // Move current rectangle down
    void move_down(float const delta);

    // Check, fro ma given mouse position, if we should change
    // the currently active rectangle i.e. the click is inside
    // the bounds of another rectangle
    void check_if_change_active_rect(sf::Vector2f const& mouse_pos);

    // Remove the currently active rectangle
    void remove_current_rect();

    // Sets the overlay text color
    void set_overlay_text_color(sf::Color const& color);

    // Get the rects to be able to print them to structures
    std::vector<sf::RectangleShape> const& get_rects() const;

    // Get the position of the sprite sheet
    sf::Vector2f get_sprite_sheet_position() const;

    // Delete copy and move
    Object_manager           (Object_manager const&) = delete;
    Object_manager& operator=(Object_manager const&) = delete;
    Object_manager           (Object_manager&&     ) = delete;
    Object_manager& operator=(Object_manager&&     ) = delete;

private:
    // Private singleton constructor
    Object_manager(sf::RenderWindow& window);

    // Default destructor
    ~Object_manager() = default;

    sf::RenderWindow&               _window;
    sf::Sprite                      _sprite_sheet;
    std::vector<sf::RectangleShape> _rects;
    std::vector<sf::Text>           _overlay_text;
    sf::Color                       _overlay_text_color;
    uint64_t                        _active_rect;
    sf::Font                        _overlay_font;
};
