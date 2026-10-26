#include "util/Assets.h"
#include "util/Log.h"

#ifndef ASSET_DIR
#define ASSET_DIR "assets/"
#endif

#include <raylib.h>

namespace util {
std::unordered_map<std::string, Texture2D> Assets::textures_;
std::unordered_map<std::string, Model> Assets::models_;
std::unordered_map<std::string, Sound> Assets::sounds_;
std::unordered_map<std::string, Font> Assets::fonts_;
std::unordered_map<std::string, Shader> Assets::shaders_;

std::string Assets::resolve(const std::string& relative) {
    return std::string(ASSET_DIR) + relative;
}

Texture2D Assets::loadTexture(const std::string& relative) {
    auto it = textures_.find(relative);
    if (it != textures_.end()) return it->second;
    const std::string path = resolve(relative);
    if (!FileExists(path.c_str())) {
        Log::warn("Missing texture: " + path);
        Texture2D t{};
        textures_[relative] = t;
        return t;
    }
    Texture2D t = LoadTexture(path.c_str());
    textures_[relative] = t;
    return t;
}

Model Assets::loadModel(const std::string& relative) {
    auto it = models_.find(relative);
    if (it != models_.end()) return it->second;
    const std::string path = resolve(relative);
    if (!FileExists(path.c_str())) {
        Log::warn("Missing model: " + path);
        Model m{};
        models_[relative] = m;
        return m;
    }
    Model m = LoadModel(path.c_str());
    models_[relative] = m;
    return m;
}

Sound Assets::loadSound(const std::string& relative) {
    auto it = sounds_.find(relative);
    if (it != sounds_.end()) return it->second;
    const std::string path = resolve(relative);
    if (!FileExists(path.c_str())) {
        Log::warn("Missing sound: " + path);
        Sound s{};
        sounds_[relative] = s;
        return s;
    }
    Sound s = LoadSound(path.c_str());
    sounds_[relative] = s;
    return s;
}

Font Assets::loadFont(const std::string& relative, int size) {
    const std::string key = relative + "#" + std::to_string(size);
    auto it = fonts_.find(key);
    if (it != fonts_.end()) return it->second;
    const std::string path = resolve(relative);
    if (!FileExists(path.c_str())) {
        Log::warn("Missing font: " + path);
        Font f = GetFontDefault();
        fonts_[key] = f;
        return f;
    }
    Font f = LoadFontEx(path.c_str(), size, nullptr, 0);
    fonts_[key] = f;
    return f;
}

Shader Assets::loadShader(const std::string& vsRel, const std::string& fsRel) {
    const std::string key = vsRel + "|" + fsRel;
    auto it = shaders_.find(key);
    if (it != shaders_.end()) return it->second;
    const std::string vs = vsRel.empty() ? std::string() : resolve(vsRel);
    const std::string fs = fsRel.empty() ? std::string() : resolve(fsRel);
    if (!vsRel.empty() && !FileExists(vs.c_str())) Log::warn("Missing vertex shader: " + vs);
    if (!fsRel.empty() && !FileExists(fs.c_str())) Log::warn("Missing fragment shader: " + fs);
    Shader s = LoadShader(vs.empty() ? nullptr : vs.c_str(), fs.empty() ? nullptr : fs.c_str());
    shaders_[key] = s;
    return s;
}

void Assets::unloadAll() {
    for (auto& kv : textures_) UnloadTexture(kv.second);
    for (auto& kv : models_) UnloadModel(kv.second);
    for (auto& kv : sounds_) UnloadSound(kv.second);
    for (auto& kv : fonts_) {
        if (kv.second.texture.id != GetFontDefault().texture.id) UnloadFont(kv.second);
    }
    for (auto& kv : shaders_) UnloadShader(kv.second);
    textures_.clear();
    models_.clear();
    sounds_.clear();
    fonts_.clear();
    shaders_.clear();
}
}
