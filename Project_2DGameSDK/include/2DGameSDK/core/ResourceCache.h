#ifndef __RESOURCE_CACHE_H__
#define __RESOURCE_CACHE_H__

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

namespace game {

  template <class TResource>
  class ResourceCache {
  public:
    virtual ~ResourceCache() {
      Clear();
    }

    virtual TResource Get(const std::string& identifier) {
      auto found = mResources.find(identifier);
      if(found != mResources.end()) {
        return found->second;
      }

      auto res = loadResource(identifier);
      return res;
    }

    virtual void Clear() {
      if(mClearPointers) {
        for(auto const& entry : mResources) {
          // TODO avoid openGL error when in runnning state
          // delete entry.second;
        }
      }
      mResources.clear();
    }

  protected:
    virtual TResource loadResource(const std::string& identifier) = 0;
    bool mClearPointers = true;
    std::map<std::string, TResource> mResources;
  };

} // namespace game

#endif