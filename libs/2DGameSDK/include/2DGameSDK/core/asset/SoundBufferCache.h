/**
 * @file SoundBufferCache.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief SoundBufferCache class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SOUND_BUFFER_CACHE_H__
#define __SOUND_BUFFER_CACHE_H__

#include <SFML/Audio.hpp>

#include <2DGameSDK/core/asset/ResourceCache.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  /**
   * @brief Loads and Caches SFML SoundBuffer Objects
   * 
   */
  class GAMESDK_DLL SoundBufferCache : public ResourceCache<sf::SoundBuffer*> {
    /**
     * @brief Function that loads or creates the requested SFML SoundBuffer
     * 
     * @param identifier The unique identifier of the SoundBuffer
     * 
     * @return The SFML SoundBuffer
     */
    sf::SoundBuffer* createResource(const std::string& identifier);

    /**
     * @brief Functions that destroys the given SFML SoundBuffer
     * 
     * @param resource The SoundBuffer to destroy
     */
    virtual void destroyResource(sf::SoundBuffer* resource);
  };
} // namespace game

#endif