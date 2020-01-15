/**
 * @file TextureCache.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Texture Cache class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __TEXTURE_CACHE_H__
#define __TEXTURE_CACHE_H__

#include <2DGameSDK/core/asset/ResourceCache.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/Graphics.hpp>

namespace game {

  /**
   * @brief Loads and Caches SFML Textures
   * 
   */
  class GAMESDK_DLL TextureCache : public ResourceCache<sf::Texture*> {

  protected:
    /**
     * @brief Function that loads or creates the requested SFML Texture
     * 
     * @param identifier The unique identifier of the Texture
     * 
     * @return The SFML Texture
     */
    sf::Texture* createResource(const std::string& identifier);

    /**
     * @brief Functions that destroys the given SFML Texture
     * 
     * @param resource The Texture to destroy
     */
    virtual void destroyResource(sf::Texture* resource);
  };
} // namespace game

#endif