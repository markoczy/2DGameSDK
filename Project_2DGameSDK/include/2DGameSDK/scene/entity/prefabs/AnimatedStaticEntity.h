/**
 * @file AnimatedStaticEntity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief AnimatedStaticEntity class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __ANIMATED_STATIC_ENTITY_H__
#define __ANIMATED_STATIC_ENTITY_H__

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/core/visual/AnimatedRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/definitions/StaticEntity.h>

namespace game {

  /**
   * @brief Static entity with animated render strategy
   * 
   */
  class GAMESDK_DLL AnimatedStaticEntity : public StaticEntity {
  public:
    /**
     * @brief Constructs a new Animated Static Entity
     * 
     * @param type the user defined type
     * @param game the game 
     * @param animationStates the animation textures
     * @param shapes the physical shapes
     * @param isCollidable wether the object is collidable
     * @param initialState the initial animation state
     */
    AnimatedStaticEntity(int type,
                         GameBase* game,
                         std::map<int, sf::Texture*> animationStates,
                         std::vector<Shape<StaticShapePhysics>*> shapes = std::vector<Shape<StaticShapePhysics>*>(),
                         bool isCollidable = false,
                         int initialState = constants::DEFAULT_ANIMATION_START);

    /**
     * @brief Sets the Size of all textures
     * 
     * @param size the new size
     */
    void SetSize(sf::Vector2f size);

    /**
     * @brief Sets the Size of a given animation state
     * 
     * @param state the animation state
     * @param size the new size
     */
    void SetSize(int state, sf::Vector2f size);

    /**
     * @brief Sets the Animation State
     * 
     * @param state the new state
     */
    void SetAnimState(int state);

  private:
    AnimatedRenderStrategy* mSpecificRenderer = nullptr;
  };

} // namespace game

#endif
