#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <SFML/Graphics.hpp>

class AssetManager {
public:
  AssetManager();
  sf::Texture& GetTexture(const std::string& filename);

private:
  std::map<std::string, sf::Texture> mTextures;
};

#endif