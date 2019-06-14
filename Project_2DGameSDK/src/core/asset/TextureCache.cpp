#include <2DGameSDK/core/asset/TextureCache.h>

namespace game {

  sf::Texture* TextureCache::createResource(const std::string& identifier) {
    auto tex = new sf::Texture();
    tex->loadFromFile(identifier);
    mResources[identifier] = tex;
    return tex;
  }

  void TextureCache::destroyResource(sf::Texture* resource) {
    delete resource;
    resource = nullptr;
  }

} // namespace game