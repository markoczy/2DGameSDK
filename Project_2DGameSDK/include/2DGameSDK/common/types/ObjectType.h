#ifndef __OBJECT_TYPE_H__
#define __OBJECT_TYPE_H__

namespace game {
  enum class ObjectType {
    Unknown = 0,
    Tile = 1,
    Entity = 2,
    Projectile = 3,
    Effect = 4
  };
} // namespace game

#endif