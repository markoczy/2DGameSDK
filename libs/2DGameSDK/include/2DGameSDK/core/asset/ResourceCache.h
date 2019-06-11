/**
 * @file ResourceCache.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief ResourceCache template
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __RESOURCE_CACHE_H__
#define __RESOURCE_CACHE_H__

#include <map>
#include <string>

#include <SFML/Graphics.hpp>

namespace game {

  /**
   * @brief Generic Template to load and cache any resource
   * 
   * @tparam TResource The resource Type
   */
  template <class TResource>
  class ResourceCache {
  public:
    virtual ~ResourceCache() {
      Clear();
    }

    /**
     * @brief Retreive a resource by it's identifier. If the resource was
     *        referenced before, the function returns the cached version. If
     *        it was not referenced before it will be loaded first.
     * 
     * @param identifier The unique identifier (e.g. path to a file)
     * 
     * @return The generic Resource
     */
    virtual TResource Get(const std::string& identifier) {
      auto found = mResources.find(identifier);
      if(found != mResources.end()) {
        return found->second;
      }

      auto res = createResource(identifier);
      return res;
    }

    /**
     * @brief Clears all resources, referencing any resource after this call
     *        leads to undefined behaviour.
     * 
     */
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
    virtual TResource createResource(const std::string& identifier) = 0;
    bool mClearPointers = true;
    std::map<std::string, TResource> mResources;
  };

} // namespace game

#endif