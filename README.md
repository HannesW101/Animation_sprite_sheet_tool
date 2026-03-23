# Animation Sprite Sheet Tool

A desktop tool for visually marking up sprite sheet animations and generating ready-to-use C++ animation data structures. Built with **C++20** and **SFML 3**.

---

## What It Does

Load a sprite sheet image, draw rectangles over each animation frame, then press **P** to export a `.h` file containing fully-formed C++ structs — `Animation`, `Frame`, `Animation_sprite_sheet`, and the matching `Animation_id` enum — ready to drop into your game engine.

---

## Features

- **Visual frame selection** — draw and resize rectangles directly over your sprite sheet
- **Multi-animation support** — rows of rectangles are grouped into separate animations automatically
- **Code generation** — exports `OUTPUT_STRUCTURES.h` with typed C++ structs and enums
- **Zoom & pan** — scroll wheel zooms toward the cursor for precise frame placement
- **Color toggle** — switch between black and white backgrounds for dark/light sprite sheets
- **Colored logger** — timestamped, file-aware console logger with per-level color coding

---

## Controls

| Input | Action |
|---|---|
| `ENTER` | Create new rectangle |
| `BACKSPACE` | Delete active rectangle |
| `D` / `A` | Increase / decrease width |
| `W` / `S` | Increase / decrease height |
| `→` `←` `↑` `↓` | Move rectangle (1 px) |
| `SHIFT` + arrow | Move rectangle (5 px) |
| `Mouse click` | Select rectangle |
| `Mouse wheel` | Zoom toward cursor |
| `C` | Toggle background color |
| `P` | Print structures to `OUTPUT_STRUCTURES.h` |

---

## Building

**Requirements:** CMake 3.28+, a C++20 compiler, and an internet connection (SFML is fetched automatically).

```bash
git clone https://github.com/HannesW101/Animation_sprite_sheet_tool.git
cd Animation_sprite_sheet_tool
cmake -S . -B build
cmake --build build
```

The executable and assets are placed in `build/bin/`.

---

## Usage

1. Put your sprite sheet in the `assets/` folder.
2. Open `src/main.cpp` and set `SPRITESHEET_NAME` to your file name:
   ```cpp
   std::string const SPRITESHEET_NAME = "my_sheet.png";
   ```
3. Build and run.
4. Draw rectangles over each animation frame. Rectangles are grouped into animations by their **Y position** and sorted left-to-right within each row.
5. Press **P** — `build/bin/OUTPUT_STRUCTURES.h` is generated.

---

## Output

Pressing **P** writes a header file like this:

```cpp
enum class Animation_id {
    ANIM_0,
    ANIM_1,
};

struct Frame {
    sf::IntRect rect;
    float       duration;
};

struct Animation {
    Animation_id       id;
    std::vector<Frame> frames;
    Animation_type     type;
    // helpers: num_frames, frame_size, next_frame, reset_curr_frame ...
};

Animation_sprite_sheet sprite_sheet = {
    "Add sf::Texture Here",
    {
        { Animation_id::ANIM_0, { {0, 0, 32, 48} }, Animation_type::LOOP },
        // ...
    },
};
```

Replace `"Add sf::Texture Here"` with your loaded `sf::Texture` and the structs are ready to use.

---

## Project Structure

```
Animation_sprite_sheet_tool/
├── assets/             # Sprite sheets and fonts go here
├── include/            # Header files
│   ├── camera.h
│   ├── input_manager.h
│   ├── logger.h
│   ├── object_manager.h
│   ├── print_manager.h
│   └── texture_manager.h
├── src/                # Source files
│   ├── main.cpp
│   ├── camera.cpp
│   ├── input_manager.cpp
│   ├── object_manager.cpp
│   ├── print_manager.cpp
│   └── texture_manager.cpp
└── CMakeLists.txt
```

---

## Dependencies

| Library | Version | Fetched via |
|---|---|---|
| [SFML](https://github.com/SFML/SFML) | 3.0.2 | CMake FetchContent |

No other dependencies. Everything else is standard C++20.

---

## License

This project currently has no license file. All rights reserved by the author unless otherwise stated.
