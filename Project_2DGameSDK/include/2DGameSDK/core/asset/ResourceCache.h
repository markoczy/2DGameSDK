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
   * @brief Generic Template to load and cache any resource. As the resources
   *        cannot be cleared in the destructor, it is best practice to Clear()
   *        the cache before deleting it.
   * 
   * @tparam TResource The resource Type
   */
  template <class TResource>
  class ResourceCache {
  public:
    /**
     * @brief Destroys the Resource Cache
     * 
     */
    ~ResourceCache() {}

    /**
     * @brief Retreives a resource by it's identifier. If the resource was
     *        referenced before, the function returns the cached version. If
     *        it was not referenced before it will be loaded first.
     * 
     * @param identifier The unique identifier (e.g. path to a file)
     * 
     * @return The generic Resource
     */
    TResource Get(const std::string& identifier) {
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
    void Clear() {
      for(auto const& entry : mResources) {
        destroyResource(entry.second);
      }
      mResources.clear();
    }

  protected:
    /**
     * @brief Function that loads or creates the requested resource
     * 
     * @param identifier The unique identifier of the resource
     * 
     * @return The generic Resource
     */
    virtual TResource createResource(const std::string& identifier) = 0;

    /**
     * @brief Functions that destroys a given resource
     * 
     * @param resource The Resource to destroy
     */
    virtual void destroyResource(TResource resource) = 0;

    std::map<std::string, TResource> mResources;
  };

} // namespace game

#endif