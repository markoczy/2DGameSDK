/**
 * @file Material.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Material struct
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __MATERIAL_H__
#define __MATERIAL_H__

namespace game {

  /**
   * @brief Contains all data that defines a Material in the Game World
   * 
   */
  struct Material {
    bool Solid, Destructive;
  };

} // namespace game

#endif