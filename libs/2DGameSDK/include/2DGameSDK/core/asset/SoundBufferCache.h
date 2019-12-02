#ifndef __SOUND_BUFFER_CACHE_H__
#define __SOUND_BUFFER_CACHE_H__

#include <SFML/Audio.hpp>

#include <2DGameSDK/core/asset/ResourceCache.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  class GAMESDK_DLL SoundBufferCache : public ResourceCache<sf::SoundBuffer*> {
    sf::SoundBuffer* createResource(const std::string& identifier);

    virtual void destroyResource(sf::SoundBuffer* resource);
  };
} // namespace game

#endif