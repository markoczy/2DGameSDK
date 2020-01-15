/**
 * @file CollisionTarget.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief CollisionTarget class 
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __COLLISION_TARGET_H__
#define __COLLISION_TARGET_H__

#include <2DGameSDK/common/types/ObjectType.h>
#include <2DGameSDK/core/GameObject.h>

namespace game {
  /**
   * @brief Defines a collision target
   * 
   */
  class CollisionTarget {
  public:
    /**
     * @brief Constructs a new Collision Target
     * 
     * @param target the target object
     * @param type the object type
     */
    CollisionTarget(void* target, ObjectType type);

    /**
     * @brief Retreives the object Type
     * 
     * @return ObjectType the type
     */
    ObjectType GetType();

    /**
     * @brief Retreives the collision Target
     * 
     * @return void* the target
     */
    void* GetTarget();

  private:
    void* mTarget;
    ObjectType mType;
  };
} // namespace game

#endif