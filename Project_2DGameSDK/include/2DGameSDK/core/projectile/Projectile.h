/**
 * @file Projectile.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Projectile class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/common/graphics/GraphicTools.h>
#include <2DGameSDK/common/types/ObjectType.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/VisualObject.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionEventType.h>
#include <2DGameSDK/physics/CollisionTarget.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/KinematicShapeDefinition.h>

namespace game {

  /**
   * @brief Defines a generic projectile
   * 
   */
  class GAMESDK_DLL Projectile : public GameObject, public VisualObject {
  public:
    /**
     * @brief Constructs a new Projectile
     * 
     * @param game the game
     * @param type the user defined projectile type
     * @param renderer the render strategy
     * @param shapes shapes the physical shapes
     * @param start the spawn point in world coordinates
     * @param velocity the velocity vector
     * @param maxLifetime the maximum lifetime (-1 for infinite)
     */
    Projectile(GameBase* game, int type, RenderStrategy* renderer, Shape<KinematicShapeDefinition>* shapes, sf::Transform start, sf::Vector2f velocity, int maxLifetime = 100);

    /**
     * @brief Destroys the Projectile
     * 
     */
    virtual ~Projectile();

    /**
     * @brief Retreives the user defined Type
     * 
     * @return int the type
     */
    virtual int GetType();

    /**
     * @brief Retreives the Z Index
     * 
     * @return int the Z Index
     */
    virtual int GetZIndex();

    /**
     * @brief Sets the Z Index
     * 
     * @param zIndex the Z Index
     */
    virtual void SetZIndex(int zIndex);

    /**
     * @brief Updates the Projectile
     * 
     */
    virtual void OnTick();

    /**
     * @brief Renders the projectile
     * 
     * @param target 
     * @param states 
     */
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

    /**
     * @brief Collision callback method
     * 
     * @param type the collision event type
     * @param arb the cpArbiter object
     * @return int the collision return value (0 don't proceed calculation,
     *         ~0 proceed calculation)
     */
    virtual int OnCollision(CollisionEventType type, cpArbiter* arb);

  protected:
    int mType;
    RenderStrategy* mRenderer = nullptr;
    Shape<KinematicShapeDefinition>* mShape;
    int mZIndex = constants::DEFAULT_ZINDEX_PROJECTILE;
    cpBody* mBody;

    int mLifetime = 1;
    int mDestructionDelay = 1;
    bool mDestroying = false;
    bool mDestroyed = false;

    void onDestroy();
  };
} // namespace game

#endif