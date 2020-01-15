/**
 * @file StaticEntity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief StaticEntity class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __STATIC_ENTITY_H__
#define __STATIC_ENTITY_H__

#include <vector>

#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/common/graphics/GraphicTools.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionTarget.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/physics/StaticShapePhysics.h>
#include <2DGameSDK/scene/entity/Entity.h>

namespace game {
  class GAMESDK_DLL StaticEntity : public Entity {
  public:
    /**
     * @brief Constructs a new Static Entity
     * 
     * @param type the user defined type
     * @param game the game 
     * @param renderer the render strategy
     * @param shapes the physical shapes
     * @param isCollidable wether the object is collidable
     */
    StaticEntity(int type,
                 GameBase* game,
                 RenderStrategy* renderer,
                 std::vector<Shape<StaticShapePhysics>*> shapes = std::vector<Shape<StaticShapePhysics>*>(),
                 bool isCollidable = false);

    /**
     * @brief Destroys the Static Entity
     * 
     */
    ~StaticEntity();

    /**
     * @brief Retreives wether the object is kinematic
     * 
     * @return bool is kinematic
     */
    virtual bool IsKinematic();

    /**
     * @brief Retreives wether the object is collidable
     * 
     * @return bool is collidable
     */
    virtual bool IsCollidable();

    /**
     * @brief Retreives the current Transform
     * 
     * @return sf::Transform the transform
     */
    virtual sf::Transform GetTransform();

    /**
     * @brief Retreives the current Accumulated Transform
     * 
     * @return sf::Transform the accumulated transform
     */
    virtual sf::Transform GetAccumulatedTransform();

    /**
     * @brief Retreives the current Combined Transform (current*accumulated)
     * 
     * @return sf::Transform 
     */
    virtual sf::Transform GetCombinedTransform();

    /**
     * @brief Retreives the current Render strategy
     * 
     * @return RenderStrategy* 
     */
    virtual RenderStrategy* GetRenderer();

    /**
     * @brief Renders the entity
     * 
     * @param target the render target
     * @param states the render states
     */
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states);

    /**
     * @brief Callback when entity has collided with another entity
     * 
     * @param type collision event type
     * @param other the other entity
     * @param arb the chipmunk arbiter
     * @return int the collision return value
     */
    virtual int OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb);

    /**
     * @brief Callback when entity has collided with another entity
     * 
     * @param type collision event type
     * @param other the other entity
     * @param arb the chipmunk arbiter
     * @return int the collision return value
     */
    virtual int OnWorldCollision(CollisionEventType type, Tile* tile, cpArbiter* arb);

  protected:
    RenderStrategy* mRenderer = nullptr;
    bool mIsCollidable;
    std::vector<Shape<StaticShapePhysics>*> mShapes;
    cpBody* mBody = nullptr;
    sf::Transform mTransform;

    /**
     * @brief Sets the Transform
     * 
     * @param transform the new tranform
     * @return bool wether the transform was set
     */
    virtual bool setTransform(sf::Transform transform);
  };
} // namespace game

#endif