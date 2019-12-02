#include <2DGameSDK/core/asset/SoundBufferCache.h>

namespace game {

  sf::SoundBuffer* SoundBufferCache::createResource(const std::string& identifier) {
    auto sound = new sf::SoundBuffer();
    sound->loadFromFile(identifier);
    mResources[identifier] = sound;
    return sound;
  }

  void SoundBufferCache::destroyResource(sf::SoundBuffer* resource) {
    delete resource;
    resource = nullptr;
  }

} // namespace game