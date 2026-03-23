// ==============================================================================
// Includes
// ------------------------------------------------------------------------------

#include "SFML/Graphics.hpp"
#include "texture_manager.h"
#include "camera.h"
#include "object_manager.h"
#include "input_manager.h"

// =============================================================================
// Configurable parameters
// -----------------------------------------------------------------------------

// Name of sprite sheet file to get animation structures for,
// must be place in "assets/..." folder
std::string const SPRITESHEET_NAME = "Example.png";

// =============================================================================
// Main
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
int main() {

    // Create the window
    sf::RenderWindow window(
        sf::VideoMode({1920u, 1080u}),
        "Animation Sprite Sheet Tool",
        sf::State::Windowed
        );

    // Get the camera
    Camera& camera = Camera::get_instance(window);

    // Get the object manager
    Object_manager& obj_man = Object_manager::get_instance(window);

    // Get the sprite sheet from the texture manager
    sf::Texture const& sprite_sheet = Texture_manager::get_texture(SPRITESHEET_NAME);

    // Get the input manager
    Input_manager& input_man = Input_manager::get_instance(window);

    // Add sprite sheet to object manager
    obj_man.add_object(sprite_sheet);

    // Background color
    sf::Color bg_color = sf::Color::Black;

    // Main loop
    while (window.isOpen()) {

        // Handle events
        while (std::optional const event = window.pollEvent()) {

            // Simple closed window event
            if (event->is<sf::Event::Closed>()) {

                window.close();
            }

            // Simple background color change event
            if (auto const key_press = event->getIf<sf::Event::KeyReleased>()) {

                // Get the keyboard key that was pressed
                sf::Keyboard::Key const key = key_press->code;

                // Check if we change background color
                if (key == sf::Keyboard::Key::C) {

                    if   (bg_color == sf::Color::Black) { bg_color = sf::Color::White; obj_man.set_overlay_text_color(sf::Color::Black); }
                    else                                { bg_color = sf::Color::Black; obj_man.set_overlay_text_color(sf::Color::White); }
                }
            }

            // Pass event to camera
            camera.update_camera(event);

            // Pass events to input manager
            input_man.handle_inputs(event);
        }

        // Clear
        window.clear(bg_color);

        // Draw
        obj_man.draw_objects();

        // Display
        window.display();
    }

    return 0;
}