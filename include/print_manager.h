// ==============================================================================
// Includes
// ------------------------------------------------------------------------------

#include "SFML/Graphics.hpp"

// ==============================================================================
// Class Print_manager
// ------------------------------------------------------------------------------

class Print_manager final {

public:
    // Get the singleton instance of the Print_manager, needs
    // window to know where the objects positions are relative to.
    static Print_manager& get_instance(sf::RenderWindow& window);

    void print_structures(std::vector<sf::RectangleShape> const& rects);

    // Delete copy and move
    Print_manager           (Print_manager const&) = delete;
    Print_manager& operator=(Print_manager const&) = delete;
    Print_manager           (Print_manager&&     ) = delete;
    Print_manager& operator=(Print_manager&&     ) = delete;

private:
    // Private singleton constructor
    Print_manager(sf::RenderWindow& window);

    // Default destructor
    ~Print_manager() = default;

    sf::RenderWindow& _window;
};
