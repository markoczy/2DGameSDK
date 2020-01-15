/**
 * @file DynamicEntity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief DynamicEntity class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __DYNAMIC_ENTITY_H__
#define __DYNAMIC_ENTITY_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/graphics/GraphicTools.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionTarget.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/physics/DynamicShapePhysics.h>
#include <2DGameSDK/scene/entity/Entity.h>

namespace game {
  /**
   * @brief Defines an Entity with a dynamic body
   * 
   */
  class GAMESDK_DLL DynamicEntity : public Entity {
  public:
    /**
     * @brief Constructs a new Dynamic Entity
     * 
     * @param type the user defined type
     * @param game the game 
     * @param renderer the render strategy
     * @param shapes the physical shapes
     * @param isCollidable wether the object is collidable
     */
    DynamicEntity(int type,
                  GameBase* game,
                  RenderStrategy* renderer,
                  std::vector<Shape<DynamicShapePhysics>*> shapes = std::vector<Shape<DynamicShapePhysics>*>(),
                  bool isCollidable = false);

    /**
     * @brief Destroys the Dynamic Entity
     * 
     */
    ~DynamicEntity();

    /**
     * @brief Retreives the current Velocity
     * 
     * @return cpVect the velocity
     */
    virtual cpVect GetVelocity();

    /**
     * @brief Retreives the current Force vector
     * 
     * @return cpVect the force vector
     */
    virtual cpVect GetForce();

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
     * @brief Sets the Mass
     * 
     * @param mass the new mass
     */
    virtual void SetMass(float mass);

    /**
     * @brief Sets the Moment
     * 
     * @param moment the new moment
     */
    virtual void SetMoment(float moment);

    /**
     * @brief Sets the Velocity
     * 
     * @param velocity the new velocity
     */
    virtual void SetVelocity(cpVect velocity);

    /**
     * @brief Sets the Force vector
     * 
     * @param force the new force
     */
    virtual void SetForce(cpVect force);

    /**
     * @brief Sets the Angular Velocity
     * 
     * @param angularVelocity the new angular velocity
     */
    virtual void SetAngularVelocity(float angularVelocity);

    /**
     * @brief Sets the Torque
     * 
     * @param torque the new torque
     */
    virtual void SetTorque(float torque);

    /**
     * @brief Renders the object
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
    std::vector<Shape<DynamicShapePhysics>*> mShapes;
    cpBody* mBody = nullptr;

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