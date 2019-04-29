#include <2DGameSDK/core/asset/AssetManager.h>

namespace game {

  TextureCache AssetManager::_textures = TextureCache();

  sf::Texture* AssetManager::GetTexture(const std::string& identifier) {
    // return _textures.Get(identifier);
    return _textures.Get(identifier);
  }

} // namespace game
