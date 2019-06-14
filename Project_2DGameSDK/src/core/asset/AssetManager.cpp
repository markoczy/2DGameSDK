#include <2DGameSDK/core/asset/AssetManager.h>

namespace game {

  TextureCache AssetManager::_textures = TextureCache();

  AssetManager::~AssetManager() {
    _textures.Clear();
  }

  sf::Texture* AssetManager::GetTexture(const std::string& identifier) {
    try {
      return _textures.Get(identifier);
    } catch(std::exception& e) {
      throw std::runtime_error("Failed to load or create texture " + identifier + ": " + e.what());
    }
  }

} // namespace game
