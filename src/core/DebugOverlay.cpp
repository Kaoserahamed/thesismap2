#include "core/DebugOverlay.h"

#include "util/Log.h"

#include <cstdio>
#include <string>

namespace core {
bool DebugOverlay::s_visible = false;
std::vector<std::string> DebugOverlay::s_lines;

void DebugOverlay::toggle() { s_visible = !s_visible; }
bool DebugOverlay::visible() { return s_visible; }
void DebugOverlay::addLine(const std::string& line) { s_lines.push_back(line); }
void DebugOverlay::clear() { s_lines.clear(); }

void DebugOverlay::draw(const std::string& stateName, float frameTime) {
    if (!s_visible) return;
    char buf[128];
    std::snprintf(buf, sizeof(buf), "FPS: %d", GetFPS());
    DrawText(buf, 10, 10, 18, LIME);
    std::snprintf(buf, sizeof(buf), "Frame: %.3f ms", frameTime * 1000.0f);
    DrawText(buf, 10, 30, 18, LIME);
    DrawText(("State: " + stateName).c_str(), 10, 50, 18, LIME);
    int y = 75;
    for (const auto& l : s_lines) {
        DrawText(l.c_str(), 10, y, 16, YELLOW);
        y += 18;
    }
    s_lines.clear();
}
}
