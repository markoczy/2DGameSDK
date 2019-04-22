#ifndef __MATERIAL_MAP_H__
#define __MATERIAL_MAP_H__

#include <2DGameSDK/world/material/Material.h>
#include <map>

namespace game {

  struct MaterialMap {
    std::map<int, Material> Materials;
  };

} // namespace game

#endif