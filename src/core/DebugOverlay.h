#pragma once
#include <raylib.h>

#include <string>
#include <vector>

namespace core {
// F1 debug overlay: FPS, frame time, current state, appendable text lines.
class DebugOverlay {
public:
    static void toggle();
    static bool visible();
    static void addLine(const std::string& line);
    static void clear();
    static void draw(const std::string& stateName, float frameTime);

private:
    static bool s_visible;
    static std::vector<std::string> s_lines;
};
}
