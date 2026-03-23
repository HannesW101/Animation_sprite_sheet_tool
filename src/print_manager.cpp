// ==============================================================================
// Includes
// ------------------------------------------------------------------------------

#include "print_manager.h"
#include "logger.h"
#include "object_manager.h"

#include <fstream>
#include <map>

// ==============================================================================
// Class Print_manager
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
Print_manager& Print_manager::get_instance(sf::RenderWindow& window) {

    static Print_manager instance(window);
    return instance;
}

// ------------------------------------------------------------------------------
void Print_manager::print_structures(std::vector<sf::RectangleShape> const& rects) {

    if (rects.empty()) {

        LOG(WARNING) << "No rectangles to print";
        return;
    }

    std::ofstream file("build/bin/OUTPUT_STRUCTURES.h");
    if (!file.is_open()) {

        LOG(ERROR) << "build/bin/OUTPUT_STRUCTURES.h";
        return;
    }

    // Group by Y
    std::map<std::size_t, std::vector<sf::RectangleShape>> rows;
    for (auto const& rect : rects) {

        std::size_t const y = static_cast<std::size_t>(rect.getPosition().y);
        rows[y].push_back(rect);
    }

    // Sort each row by X
    for (auto& [y, row] : rows) {

        std::sort(row.begin(), row.end(), [](sf::RectangleShape const& a, sf::RectangleShape const& b) {

            return (a.getPosition().x < b.getPosition().x);
            });
    }

    std::size_t const num_anims = rows.size();

    // enum class Animation_id
    file << "enum class Animation_id {\n\n";
    for (std::size_t i = 0u; i < num_anims; ++i) {

        file << "    ANIM_" << i << ",\n";
    }
    file << "};\n\n";

    // enum class Animation_type
    file << "enum class Animation_type {\n\n"
            "    LOOP,\n"
            "    ONE_SHOT,\n"
            "    PING_PONG,\n"
            "    HOLD\n"
            "};\n\n";

    // struct Frame
    file << "struct Frame {\n\n"
            "    sf::IntRect rect;\n"
            "    float       duration;\n"
            "};\n\n";

    // struct Animation
    file << "struct Animation {\n\n"
            "    Animation_id       id;\n"
            "    std::vector<Frame> frames;\n"
            "    Animation_type     type;\n"
            "\n"
            "    std::size_t  num_frames             (/*----------------*/) const { return frames.size();                                             }\n"
            "    sf::Vector2i frame_size             (/*----------------*/) const { return frames.empty() ? sf::Vector2i{0,0} : frames[0u].rect.size; }\n"
            "    void         set_all_frame_durations(float const duration)       { for (auto& f : frames) { f.duration = duration; }                 }\n"
            "    std::size_t  get_curr_frame         (/*----------------*/) const { return _curr_frame;                                               }\n"
            "    void         reset_curr_frame       (/*----------------*/)       { _curr_frame = 0u;                                                 }\n"
            "    void         next_frame             (/*----------------*/)       { _curr_frame = (_curr_frame + 1u) % num_frames();                  }\n"
            "\n"
            "private:\n"
            "    std::size_t _curr_frame = 0u;\n"
            "};\n\n";

    // struct Animation_sprite_sheet
    file << "struct Animation_sprite_sheet {\n\n"
            "    sf::Texture            texture;\n"
            "    std::vector<Animation> animations;\n"
            "\n"
            "    Animation const* findc(Animation_id const id) const {\n"
            "\n"
            "        for (auto const& a : animations) {\n"
            "\n"
            "            if (a.id == id) { return &a; }\n"
            "        }\n"
            "\n"
            "        return nullptr;\n"
            "    }\n"
            "\n"
            "    Animation* find(Animation_id const id) {\n"
            "\n"
            "        for (auto& a : animations) {\n"
            "\n"
            "            if (a.id == id) { return &a; }\n"
            "        }\n"
            "\n"
            "        return nullptr;\n"
            "    }\n"
            "};\n\n";

    // data
    file << "Animation_sprite_sheet sprite_sheet = {\n";
    file << "    \"Add sf::Texture Here\",\n";
    file << "    {\n";

    std::size_t anim_idx = 0u;
    sf::Vector2f const sheet_pos = Object_manager::get_instance(_window).get_sprite_sheet_position();
    for (auto const& [y, row] : rows) {

        file << "        {\n";
        file << "            Animation_id::ANIM_" << anim_idx << ",\n";
        file << "            {\n";

        for (auto const& rect : row) {

            float const rx = rect.getPosition().x - sheet_pos.x;
            float const ry = rect.getPosition().y - sheet_pos.y;
            float const rw = rect.getSize().x;
            float const rh = rect.getSize().y;

            file << "                { {" << rx << ", " << ry << ", " << rw << ", " << rh << "} },\n";
        }

        file << "            },\n";
        file << "            Animation_type::LOOP\n";
        file << "        },\n";

        ++anim_idx;
    }

    file << "    },\n";
    file << "};\n";

    file.close();

    LOG(INFO) << "Printed " << anim_idx << " animations to OUTPUT_STRUCTURES.h";
}

// ------------------------------------------------------------------------------
Print_manager::Print_manager(sf::RenderWindow& window)
    : _window(window)
{}
