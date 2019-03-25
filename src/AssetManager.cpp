#include "AssetManager.h"

using namespace sf;
using namespace std;

AssetManager::AssetManager() {}

Texture& AssetManager::GetTexture(const string& filename) {
  auto found = mTextures.find(filename);
  if(found != mTextures.end()) {
    return found->second;
  }

  auto& tex = mTextures[filename];
  tex.loadFromFile(filename);
  return tex;
}