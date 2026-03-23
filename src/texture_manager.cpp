// ==============================================================================
// Includes
// ------------------------------------------------------------------------------

#include "texture_manager.h"
#include "logger.h"

#include "SFML/Graphics.hpp"

// ==============================================================================
// Class Texture_manager
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
sf::Texture const& Texture_manager::get_texture(std::string const& texture_name) {

    // Static singleton instance
    static Texture_manager instance;

    // Build file path for texture
    std::string const file_path = "assets/" + texture_name;

    // Load texture
    if (!instance._texture.loadFromFile(file_path)) {

        // Failed to load
        LOG(ERROR) << "Failed to load texture [" << texture_name << ']';
    }

    return instance._texture;
}

// ------------------------------------------------------------------------------
sf::Texture const& Texture_manager::get_default_texture(){

    // Static singleton instance
    static Texture_manager instance;

    // Build file path for texture
    std::string const file_path = "assets/Default_texture.png";

    // Load texture
    if (!instance._texture.loadFromFile(file_path)) {

        // Failed to load
        LOG(ERROR) << "Failed to load texture [Default_texture]";
    }

    return instance._default_texture;
}

// ------------------------------------------------------------------------------
Texture_manager::Texture_manager()
    : _texture()
{}
