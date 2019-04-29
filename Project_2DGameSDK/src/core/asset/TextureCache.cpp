#include <2DGameSDK/core/asset/TextureCache.h>

namespace game {

  sf::Texture* TextureCache::loadResource(const std::string& identifier) {
    auto tex = new sf::Texture();
    tex->loadFromFile(identifier);
    mResources[identifier] = tex;
    return tex;
  }

  sf::Texture* TextureCache::Get(const std::string& identifier) { return ResourceCache::Get(identifier); };
  void TextureCache::Clear(){};

} // namespace game