// ==============================================================================
// Includes
// ------------------------------------------------------------------------------

#include "input_manager.h"
#include "object_manager.h"
#include "print_manager.h"

// ==============================================================================
// Class Input_manager
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
Input_manager& Input_manager::get_instance(sf::RenderWindow& window) {

    static Input_manager instance(window);
    return instance;
}

// ------------------------------------------------------------------------------
Input_manager::Input_manager(sf::RenderWindow& window)
    : _window(window)
    {

    // Add all overlay text to the window
    _add_all_overlay_controls();
}

// ------------------------------------------------------------------------------
void Input_manager::handle_inputs(std::optional<sf::Event> const& event) {

    // Check if there is a keyboard press event
    if (auto const key_press = event->getIf<sf::Event::KeyPressed>()) {

        // Get the keyboard key that was pressed
        sf::Keyboard::Key const key = key_press->code;

        // Check if holding down shift
        bool const shift = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift);

        // Dispatch event accordingly
             if (key == sf::Keyboard::Key::D        ) { _key_pressed__d();                                           }
        else if (key == sf::Keyboard::Key::A        ) { _key_pressed__a();                                           }
        else if (key == sf::Keyboard::Key::W        ) { _key_pressed__w();                                           }
        else if (key == sf::Keyboard::Key::S        ) { _key_pressed__s();                                           }
        else if (key == sf::Keyboard::Key::Right    ) { shift ? _key_pressed__shift_right() : _key_pressed__right(); }
        else if (key == sf::Keyboard::Key::Left     ) { shift ? _key_pressed__shift_left()  : _key_pressed__left();  }
        else if (key == sf::Keyboard::Key::Up       ) { shift ? _key_pressed__shift_up()    : _key_pressed__up();    }
        else if (key == sf::Keyboard::Key::Down     ) { shift ? _key_pressed__shift_down()  : _key_pressed__down();  }
        else if (key == sf::Keyboard::Key::Enter    ) { _key_pressed__enter();                                       }
        else if (key == sf::Keyboard::Key::Backspace) { _key_pressed__backspace();                                   }
        else if (key == sf::Keyboard::Key::P        ) { _key_pressed__p();                                           }
    }

    // Check if there is a mouse button release event
    if (auto const mouse_released = event->getIf<sf::Event::MouseButtonReleased>()) {

        // Get the keyboard key that was pressed
        sf::Mouse::Button const mouse_btn = mouse_released->button;

        // Check if left button released
        if (mouse_btn == sf::Mouse::Button::Left) { _mouse_released__left(); }
    }
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__d() const {

    Object_manager::get_instance(_window).increase_width(1.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__a() const {

    Object_manager::get_instance(_window).decrease_width(1.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__w() const {

    Object_manager::get_instance(_window).increase_height(1.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__s() const {

    Object_manager::get_instance(_window).decrease_height(1.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__right() const {

    Object_manager::get_instance(_window).move_right(1.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__left() const {

    Object_manager::get_instance(_window).move_left(1.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__up() const {

    Object_manager::get_instance(_window).move_up(1.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__down() const {

    Object_manager::get_instance(_window).move_down(1.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__shift_right() const {

    Object_manager::get_instance(_window).move_right(5.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__shift_left() const {

    Object_manager::get_instance(_window).move_left(5.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__shift_up() const {

    Object_manager::get_instance(_window).move_up(5.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__shift_down() const {

    Object_manager::get_instance(_window).move_down(5.0f);
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__enter() const {

    Object_manager::get_instance(_window).add_object(sf::Vector2f{50.0f, 50.0f});
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__backspace() const {

    Object_manager::get_instance(_window).remove_current_rect();
}

// ------------------------------------------------------------------------------
void Input_manager::_key_pressed__p() const {

    auto const& rects = Object_manager::get_instance(_window).get_rects();
    Print_manager::get_instance(_window).print_structures(rects);
}

// ------------------------------------------------------------------------------
void Input_manager::_mouse_released__left() const {

    // Get mouse pos in pixels
    sf::Vector2i const mouse_pos_px = sf::Mouse::getPosition(_window);

    // Convert to world co-ordinates
    sf::Vector2f const mouse_pos_world_coords = _window.mapPixelToCoords(mouse_pos_px);

    // Give this to object manager to check if we must change rectangle
    Object_manager::get_instance(_window).check_if_change_active_rect(mouse_pos_world_coords);
}

// ------------------------------------------------------------------------------
void Input_manager::_add_all_overlay_controls() const {

    Object_manager::get_instance(_window).add_object("[C] Change color");
    Object_manager::get_instance(_window).add_object("[ENTER] Create rectangle");
    Object_manager::get_instance(_window).add_object("[BACKSPACE] Delete rectangle");
    Object_manager::get_instance(_window).add_object("[P] Print structures");
    Object_manager::get_instance(_window).add_object("[D] Increase width");
    Object_manager::get_instance(_window).add_object("[A] Decrease width");
    Object_manager::get_instance(_window).add_object("[W] Increase height");
    Object_manager::get_instance(_window).add_object("[S] Decrease height");
    Object_manager::get_instance(_window).add_object("[>] Move right");
    Object_manager::get_instance(_window).add_object("[<] Move left");
    Object_manager::get_instance(_window).add_object("[^] Move up");
    Object_manager::get_instance(_window).add_object("[v] Move down");
    Object_manager::get_instance(_window).add_object("[SHIFT] Hold to move fast");
    Object_manager::get_instance(_window).add_object("[MOUSE WHEEL] Zoom");
}