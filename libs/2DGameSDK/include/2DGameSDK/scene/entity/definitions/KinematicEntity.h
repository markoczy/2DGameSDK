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
   * @brief Abstract class that defines an Entity that is Transformable and can
   *        be placed on the SceneGraph.
   * 
   */
  class GAMESDK_DLL KinematicEntity : public Entity {
  public:
    /**
     * @brief Creates a new Transformable Entity object
     * 
     * @param type type The Entity Type (does not affect anything and is meant
     *        to be used freely to identify entities of some kind)
     */
    KinematicEntity(int type, GameBase* game, RenderStrategy* renderer, std::vector<Shape<KinematicShapePhysics>*> shapes = std::vector<Shape<KinematicShapePhysics>*>(), bool isCollidable = false);

    /**
     * @brief Destroys the Transformable Entity object
     * 
     */
    virtual ~KinematicEntity();

    virtual bool IsKinematic();
    virtual bool IsCollidable();

    virtual sf::Transform GetTransform();
    virtual sf::Transform GetAccumulatedTransform();
    virtual sf::Transform GetCombinedTransform();
    virtual RenderStrategy* GetRenderer();

    virtual void OnTickEnded();
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