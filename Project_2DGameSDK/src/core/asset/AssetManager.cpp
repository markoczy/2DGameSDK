#include <2DGameSDK/core/asset/AssetManager.h>

namespace game {

  TextureCache AssetManager::_textures = TextureCache();
  SoundBufferCache AssetManager::_sounds = SoundBufferCache();

  AssetManager::~AssetManager() {
    _textures.Clear();
    _sounds.Clear();
  }

  sf::Texture* AssetManager::GetTexture(const std::string& identifier) {
    try {
      return _textures.Get(identifier);
    } catch(std::exception& e) {
      throw std::runtime_error("Failed to load or create texture " + identifier + ": " + e.what());
    }
  }

  sf::SoundBuffer* AssetManager::GetAudio(const std::string& identifier) {
    try {
      return _sounds.Get(identifier);
    } catch(std::exception& e) {
      throw std::runtime_error("Failed to load or create sound " + identifier + ": " + e.what());
    }
  }

} // namespace game
