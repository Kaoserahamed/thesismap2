#pragma once
#include <raylib.h>

#include <string>
#include <unordered_map>

namespace util {
// Loader helpers with caching for raylib resources; reports missing files via Log.
class Assets {
public:
    static std::string resolve(const std::string& relative);
    static Texture2D loadTexture(const std::string& relative);
    static Model loadModel(const std::string& relative);
    static Sound loadSound(const std::string& relative);
    static Font loadFont(const std::string& relative, int size = 32);
    static Shader loadShader(const std::string& vsRel, const std::string& fsRel);
    static void unloadAll();

private:
    static std::unordered_map<std::string, Texture2D> textures_;
    static std::unordered_map<std::string, Model> models_;
    static std::unordered_map<std::string, Sound> sounds_;
    static std::unordered_map<std::string, Font> fonts_;
    static std::unordered_map<std::string, Shader> shaders_;
};
}
