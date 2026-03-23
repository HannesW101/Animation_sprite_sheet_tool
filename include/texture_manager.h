// ==============================================================================
// Includes
// ------------------------------------------------------------------------------

#include "SFML/Graphics.hpp"

#include <string>

// ==============================================================================
// Class Texture_manager
// ------------------------------------------------------------------------------

class Texture_manager final {

public:
    // Get texture, simple as we only should have one texture we need to
    // get. This will add the "assets/..." path automatically for you.
    static sf::Texture const& get_texture(std::string const& texture_name);
    static sf::Texture const& get_default_texture();

    // Delete copy and move
    Texture_manager           (Texture_manager const&) = delete;
    Texture_manager& operator=(Texture_manager const&) = delete;
    Texture_manager           (Texture_manager&&     ) = delete;
    Texture_manager& operator=(Texture_manager&&     ) = delete;

private:
    // Private for singleton
    Texture_manager();

    // Default destructor
    ~Texture_manager() = default;

    sf::Texture _texture;
    sf::Texture _default_texture;
};
