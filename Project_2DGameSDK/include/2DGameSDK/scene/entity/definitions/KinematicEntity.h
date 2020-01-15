/**
 * @file KinematicEntity.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Kinematic Entity class
 * @version 1.0
 * @date 2019-06-13
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __KINEMATIC_ENTITY_H__
#define __KINEMATIC_ENTITY_H__

#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionEventType.h>
#include <2DGameSDK/physics/CollisionTarget.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/physics/KinematicShapePhysics.h>
#include <2DGameSDK/scene/entity/Entity.h>

#include <SFML/Graphics.hpp>

namespace game {
  // Forward declaration
  class SceneGraphNode;

  /**
   * @brief Abstract class that defines an Entity that is kinematic and can
   *        be placed on the SceneGraph.
   * 
   */
  class GAMESDK_DLL KinematicEntity : public Entity {
  public:
    /**
     * @brief Constructs a new Kinematic Entity
     * 
     * @param type the user defined type
     * @param game the game 
     * @param renderer the render strategy
     * @param shapes the physical shapes
     * @param isCollidable wether the object is collidable
     */
    KinematicEntity(int type, GameBase* game, RenderStrategy* renderer, std::vector<Shape<KinematicShapePhysics>*> shapes = std::vector<Shape<KinematicShapePhysics>*>(), bool isCollidable = false);

    /**
     * @brief Destroys the Transformable Entity object
     * 
     */
    virtual ~KinematicEntity();

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
     * @brief After Update Callback
     * 
     */
    virtual void OnTickEnded();

    /**
     * @brief Renders the entity
     * 
     * @param target the render target
     * @param states the render states
     */
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states);

  protected:
    RenderStrategy* mRenderer = nullptr;
    std::vector<Shape<KinematicShapePhysics>*> mShapes;
    bool mIsCollidable;
    sf::Transform mTransform;
    sf::Transform mAccTransform;
    sf::Transform mCombinedTransform;
    cpBody* mBody = nullptr;

    virtual bool setTransform(sf::Transform transform);
    virtual bool transform(sf::Transform transform);
    virtual bool setAccumulatedTransform(sf::Transform accumulated);
  };

} // namespace game

#endif