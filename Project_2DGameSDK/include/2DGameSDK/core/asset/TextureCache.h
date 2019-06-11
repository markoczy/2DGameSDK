/**
 * @file TextureCache.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Texture Cache class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
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
  public:
    /**
     * @brief Returns an SFML texture by it's identifier
     * 
     * @param identifier the unique identifier (i.e. path to the file)
     * 
     * @return The loaded or previously cached SFML Texture
     */
    virtual sf::Texture* Get(const std::string& identifier);

    /**
     * @brief Clears all cached SFML Textures
     */
    virtual void Clear();

  protected:
    /**
     * @brief Private function to load the resource
     */
    sf::Texture* createResource(const std::string& identifier);
  };
} // namespace game

#endif