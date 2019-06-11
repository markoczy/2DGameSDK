#include <2DGameSDK/core/asset/TextureCache.h>

namespace game {

  sf::Texture* TextureCache::createResource(const std::string& identifier) {
    auto tex = new sf::Texture();
    tex->loadFromFile(identifier);
    mResources[identifier] = tex;
    return tex;
  }

  void TextureCache::destroyResource(sf::Texture* resource) {
    // TODO avoid openGL error when in runnning state
    //delete resource;
  }

  sf::Texture* TextureCache::Get(const std::string& identifier) { return ResourceCache::Get(identifier); };
  void TextureCache::Clear(){};

} // namespace game