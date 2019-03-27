#ifndef __RESOURCE_CACHE_H__
#define __RESOURCE_CACHE_H__

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

template <class TResource>
class ResourceCache {
public:
  virtual ~ResourceCache();
  virtual TResource Get(const std::string& identifier);
  virtual void Clear();

protected:
  virtual TResource loadResource(const std::string& identifier) = 0;
  bool mClearPointers = true;
  std::map<std::string, TResource> mResources;
};

class TextureCache : public ResourceCache<sf::Texture*> {
  sf::Texture* loadResource(const std::string& identifier);
};

#endif