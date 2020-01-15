/**
 * @file EntityFactory.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief EntityFactory class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __ENTITY_FACTORY_H__
#define __ENTITY_FACTORY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/scene/entity/definitions/DynamicEntity.h>

namespace game {
  /**
   * @brief Provides factory methods to create entities
   * 
   */
  class GAMESDK_DLL EntityFactory {
  public:
    /**
     * @brief Creates a Single Sprite Dynamic Entity
     * 
     * @param type the user defined type
     * @param game the game 
     * @param texture the render texture
     * @param shapes the physical shapes
     * @param size the size
     * @param isCollidable wether the object is collidable
     * @return DynamicEntity the entity
     */
    static DynamicEntity CreateSingleSpriteDynamicEntity(int type, GameBase* game, sf::Texture* texture, std::vector<Shape<DynamicShapePhysics>*> shapes, sf::Vector2f size = constants::DIMENSION_USE_DEFAULT, bool isCollidable = false);

    /**
     * @brief Creates a Animated Dynamic Entity
     * 
     * @param type the user defined type
     * @param game the game 
     * @param texture the texture
     * @param shapes the physical shapes
     * @param size the size
     * @param isCollidable wether the object is collidable
     * @return DynamicEntity the entity
     */
    static DynamicEntity CreateAnimatedDynamicEntity(int type, GameBase* game, sf::Texture* texture, std::vector<Shape<DynamicShapePhysics>*> shapes, sf::Vector2f size = constants::DIMENSION_USE_DEFAULT, bool isCollidable = false);
  };

} // namespace game

#endif