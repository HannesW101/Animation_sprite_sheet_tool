// ==============================================================================
// Includes
// ------------------------------------------------------------------------------

#include "object_manager.h"
#include "texture_manager.h"
#include "logger.h"

#include <ranges>

// ==============================================================================
// Class Object_manager
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
Object_manager& Object_manager::get_instance(sf::RenderWindow& window) {

    static Object_manager instance(window);
    return instance;
}

// ------------------------------------------------------------------------------
Object_manager::Object_manager(sf::RenderWindow& window)
    : _window(window)
    , _sprite_sheet(Texture_manager::get_default_texture())
    , _rects()
    , _overlay_text()
    , _overlay_text_color(sf::Color::White)
    , _active_rect(0u)
    , _overlay_font()
    {

    // Load font
    if (!_overlay_font.openFromFile("assets/BoldPixels.ttf")) {

        LOG(ERROR) << "Failed to load overlay text";
    }
}

// ------------------------------------------------------------------------------
void Object_manager::add_object(sf::Texture const& sprite_sheet) {

    // Set the sprite sheet
    _sprite_sheet = sf::Sprite(sprite_sheet);
}

// ------------------------------------------------------------------------------
void Object_manager::add_object(sf::Vector2f const& size) {

    // Make a rect with this size
    sf::RectangleShape rect(size);

    // Set position to center of window
    float const win_center_x = static_cast<float>(_window.getSize().x / 2.0f);
    float const win_center_y = static_cast<float>(_window.getSize().y / 2.0f);
    rect.setPosition({
        win_center_x,
        win_center_y
        });

    // Make opacity 0 for inside of rect
    rect.setFillColor(sf::Color(255u, 255u, 255u, 0u));

    // Add red border for clarity
    rect.setOutlineThickness(1.0f);
    rect.setOutlineColor(sf::Color::Red);

    // Add to the vector
    _rects.push_back(rect);

    // After we add a new rectangle, make it the active rectangle
    _active_rect = _rects.size() - 1u;
}

// ------------------------------------------------------------------------------
void Object_manager::add_object(std::string const& text) {

    // Make a sf::Text with this string and our own font
    sf::Text t(_overlay_font, text);

    // Set text character size
    t.setCharacterSize(20u);

    // Get window height
    float const win_height = static_cast<float>(_window.getSize().y);

    // Vertical gap between text
    float const text_gap = 40.0f;

    // If its the first item of the overlay position at the bottom left corner
    if (_overlay_text.empty()) {

        // Position bottom left
        t.setPosition({
            15.0f,
            win_height - 20.0f - text_gap
        });

    // If its not the first, then position above last text bottom left corner
    } else {

        // Get offset to place above last text
        float const offset_y = _overlay_text.back().getPosition().y;

        // Position bottom left above last text
        t.setPosition({
            15.0f,
            offset_y - text_gap
        });
    }

    _overlay_text.push_back(t);
}

// ------------------------------------------------------------------------------
void Object_manager::draw_objects() {

    // Draw sprite sheet center of window
    float const win_center_x          = static_cast<float>(_window.getSize().x / 2.0f);
    float const win_center_y          = static_cast<float>(_window.getSize().y / 2.0f);
    float const sprite_sheet_center_x = _sprite_sheet.getGlobalBounds().size.x / 2.0f;
    float const sprite_sheet_center_y = _sprite_sheet.getGlobalBounds().size.y / 2.0f;
    _sprite_sheet.setPosition({
        win_center_x - sprite_sheet_center_x,
        win_center_y - sprite_sheet_center_y
        });
    _window.draw(_sprite_sheet);

    // Draw all rectangles to window
    for (std::size_t rect_idx = 0u; rect_idx < _rects.size(); ++rect_idx) {

        // Active rectangle is red
        if (rect_idx == _active_rect) {

            _rects[rect_idx].setOutlineColor(sf::Color::Red);

        // Non active rectangles is blue
        } else {

            _rects[rect_idx].setOutlineColor(sf::Color::Blue);
        }

        // Draw rectangle
        _window.draw(_rects[rect_idx]);
    }

    // Draw overlay text to window
    // Switch view so overlay text is fixed to the corner
    sf::View const prev_view = _window.getView();
    _window.setView(_window.getDefaultView());

    for (auto& text : _overlay_text) {

        text.setFillColor(_overlay_text_color);
        _window.draw(text);
    }

    // Restore camera view
    _window.setView(prev_view);
}

// ------------------------------------------------------------------------------
void Object_manager::increase_width(float const delta) {

    // Increase width
    _rects[_active_rect].setSize({
        _rects[_active_rect].getSize().x + delta,
        _rects[_active_rect].getSize().y
        });
}

// ------------------------------------------------------------------------------
void Object_manager::decrease_width(float const delta) {

    // Decrease width only if its not 0
    if (_rects[_active_rect].getSize().x == 0) {

        // Do nothing
    } else {

        _rects[_active_rect].setSize({
            _rects[_active_rect].getSize().x - delta,
            _rects[_active_rect].getSize().y
            });
    }
}

// ------------------------------------------------------------------------------
void Object_manager::increase_height(float const delta) {

    // Increase height
    _rects[_active_rect].setSize({
        _rects[_active_rect].getSize().x,
        _rects[_active_rect].getSize().y + delta
        });
}

// ------------------------------------------------------------------------------
void Object_manager::decrease_height(float const delta) {

    // Decrease height only if its not 0
    if (_rects[_active_rect].getSize().y == 0) {

        // Do nothing
    } else {

        _rects[_active_rect].setSize({
            _rects[_active_rect].getSize().x,
            _rects[_active_rect].getSize().y - delta
            });
    }
}

// ------------------------------------------------------------------------------
void Object_manager::move_right(float const delta) {

    _rects[_active_rect].move({
        delta,
        0.0f
        });
}

// ------------------------------------------------------------------------------
void Object_manager::move_left(float const delta) {

    _rects[_active_rect].move({
        -delta,
        0.0f
        });
}

// ------------------------------------------------------------------------------
void Object_manager::move_up(float const delta) {

    _rects[_active_rect].move({
        0.0f,
        -delta
        });
}

// ------------------------------------------------------------------------------
void Object_manager::move_down(float const delta) {

    _rects[_active_rect].move({
        0.0f,
        delta
        });
}

// ------------------------------------------------------------------------------
void Object_manager::check_if_change_active_rect(sf::Vector2f const& mouse_pos) {

    // If we have no rectangles just do nothing
    if (_rects.empty()) {

        return;
    }

    // Loop through rectangles and check if any is inside mouse bounds
    // and if any are, set it to the current active rectangle. Loop
    // backwards as intuitively the rectangle on top should be favored
    for (std::size_t rect_idx = _rects.size(); rect_idx-- > 0u;) {

        if (_rects[rect_idx].getGlobalBounds().contains(mouse_pos)) {

            _active_rect = rect_idx;
            break;
        }
    }
}

// ------------------------------------------------------------------------------
void Object_manager::remove_current_rect() {

    _rects.erase(_rects.cbegin() +  _active_rect);
}

// ------------------------------------------------------------------------------
void Object_manager::set_overlay_text_color(sf::Color const& color) {

    _overlay_text_color = color;
}

// ------------------------------------------------------------------------------
std::vector<sf::RectangleShape> const& Object_manager::get_rects() const {

    return _rects;
}

// ------------------------------------------------------------------------------
sf::Vector2f Object_manager::get_sprite_sheet_position() const {

    return _sprite_sheet.getPosition();
}