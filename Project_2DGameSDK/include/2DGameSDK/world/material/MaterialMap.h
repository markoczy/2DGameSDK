/**
 * @file MaterialMap.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Material Map struct
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __MATERIAL_MAP_H__
#define __MATERIAL_MAP_H__

#include <2DGameSDK/world/material/Material.h>
#include <map>

namespace game {
  /**
   * @brief Contains a Mapping between the Tile ID and the Material
   * 
   */
  struct MaterialMap {
    std::map<int, Material> Materials = std::map<int, Material>();
  };

} // namespace game

#endif