#include <2DGameSDK/core/ResourceCache.h>

using namespace std;

template <class TResource>
ResourceCache<TResource>::~ResourceCache() {
  Clear();
}

template <class TResource>
TResource ResourceCache<TResource>::Get(const string& identifier) {
  auto found = mResources.find(identifier);
  if(found != mResources.end()) {
    return found->second;
  }

  auto res = loadResource(identifier);
  return res;
}

template <class TResource>
void ResourceCache<TResource>::Clear() {
  if(mClearPointers) {
    for(auto const& entry : mResources) {
      delete entry.second;
    }
  }
  mResources.clear();
}

sf::Texture* TextureCache::loadResource(const std::string& identifier) {
  auto tex = new sf::Texture();
  tex->loadFromFile(identifier);
  mResources[identifier] = tex;
  return tex;
}

sf::Texture* TextureCache::Get(const std::string& identifier) { return ResourceCache::Get(identifier); };
void TextureCache::Clear(){};