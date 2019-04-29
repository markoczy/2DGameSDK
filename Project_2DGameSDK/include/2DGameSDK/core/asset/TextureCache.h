#ifndef __TEXTURE_CACHE_H__
#define __TEXTURE_CACHE_H__

#include <2DGameSDK/core/ResourceCache.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/Graphics.hpp>

namespace game {

  class GAMESDK_DLL TextureCache : public ResourceCache<sf::Texture*> {
  public:
    virtual sf::Texture* Get(const std::string& identifier);
    virtual void Clear();

  private:
    sf::Texture* loadResource(const std::string& identifier);
  };
} // namespace game

#endif