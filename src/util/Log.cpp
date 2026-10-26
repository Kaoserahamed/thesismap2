#include "util/Log.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>

namespace util {

namespace {
std::ofstream g_file;
std::mutex g_mutex;
bool g_ready = false;

std::string timestamp() {
    const auto now = std::chrono::system_clock::now();
    const std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    std::ostringstream os;
    os << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return os.str();
}

void write(const char* level, const std::string& msg) {
    std::lock_guard<std::mutex> lock(g_mutex);
    const std::string line = "[" + timestamp() + "] [" + level + "] " + msg;
    std::cout << line << "\n";
    if (g_ready && g_file.is_open()) {
        g_file << line << "\n";
        g_file.flush();
    }
}
}

void Log::init(const std::string& path) {
    std::lock_guard<std::mutex> lock(g_mutex);
    std::filesystem::path p(path);
    if (p.has_parent_path()) {
        std::error_code ec;
        std::filesystem::create_directories(p.parent_path(), ec);
    }
    g_file.open(path, std::ios::app);
    g_ready = g_file.is_open();
}

void Log::info(const std::string& msg) { write("INFO", msg); }
void Log::warn(const std::string& msg) { write("WARN", msg); }
void Log::error(const std::string& msg) { write("ERROR", msg); }

}
