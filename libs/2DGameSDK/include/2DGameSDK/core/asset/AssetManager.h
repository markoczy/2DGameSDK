#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <2DGameSDK/core/asset/TextureCache.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/Graphics.hpp>

namespace game {

  class GAMESDK_DLL AssetManager {
  public:
    static sf::Texture* GetTexture(const std::string& identifier);

  private:
    static TextureCache _textures;
  };

} // namespace game

#endif