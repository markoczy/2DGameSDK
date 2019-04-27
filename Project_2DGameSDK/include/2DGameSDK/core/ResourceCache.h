#ifndef __RESOURCE_CACHE_H__
#define __RESOURCE_CACHE_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <map>
#include <string>

#include <SFML/Graphics.hpp>

template <class TResource>
class GAMESDK_DLL ResourceCache {
public:
  virtual ~ResourceCache();
  virtual TResource Get(const std::string& identifier);
  virtual void Clear();

protected:
  virtual TResource loadResource(const std::string& identifier) = 0;
  bool mClearPointers = true;
  std::map<std::string, TResource> mResources;
};

class GAMESDK_DLL TextureCache : public ResourceCache<sf::Texture*> {
public:
  virtual sf::Texture* Get(const std::string& identifier);
  virtual void Clear();

private:
  sf::Texture* loadResource(const std::string& identifier);
};

#endif