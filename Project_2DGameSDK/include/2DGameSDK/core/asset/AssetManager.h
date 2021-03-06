/**
 * @file AssetManager.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Asset Manager Class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <2DGameSDK/core/asset/SoundBufferCache.h>
#include <2DGameSDK/core/asset/TextureCache.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace game {
  /**
   * @brief Static class that Loads and Caches all Assets (images, sounds etc.) 
   *        used for the 2DGameSDK
   * 
   */
  class GAMESDK_DLL AssetManager {
  public:
    /**
     * @brief Destroys the Asset Manager
     * 
     */
    ~AssetManager();

    /**
     * @brief Returns an SFML texture by it's identifier
     * 
     * @param identifier the unique identifier (i.e. path to the file)
     * 
     * @return The loaded or previously cached SFML Texture
     */
    static sf::Texture* GetTexture(const std::string& identifier);

    /**
     * @brief Returns an SFML SoundBuffer by it's identifier
     * 
     * @param identifier the unique identifier (i.e. path to the file)
     * @return sf::SoundBuffer* The loaded or previously cached SFML SoundBuffer
     */
    static sf::SoundBuffer* GetAudio(const std::string& identifier);

  private:
    static TextureCache _textures;
    static SoundBufferCache _sounds;
  };

} // namespace game

#endif