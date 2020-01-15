/**
 * @file BoundedFollowCameraController.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief BoundedFollowCameraController class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __BOUNDED_FOLLOW_CAMERA_CONTROLLER_H__
#define __BOUNDED_FOLLOW_CAMERA_CONTROLLER_H__

#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/camera/CameraController.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/Entity.h>
#include <2DGameSDK/world/GameWorld.h>

namespace game {
  /**
   * @brief Camera that follows the player but never exits the world bounds
   * 
   */
  class GAMESDK_DLL BoundedFollowCameraController : public CameraController {
  public:
    /**
     * @brief Constructs a new Bounded Follow Camera Controller
     * 
     * @param game the game
     * @param entity the entity to follow
     * @param enableRotation wether rotation should be adapted
     */
    BoundedFollowCameraController(GameBase* game, Entity* entity, bool enableRotation = false);

    /**
     * @brief Retreives the camera Bounds
     * 
     * @return sf::Vector2f the camera bounds
     */
    virtual sf::Vector2f GetBounds();

    /**
     * @brief Sets the Zoom
     * 
     * @param zoom the new zoom
     */
    virtual void SetZoom(float zoom);

    /**
     * @brief Sets the Center
     * 
     * @param center the new center
     */
    virtual void SetCenter(sf::Vector2f center);

    /**
     * @brief Updates the Camera Controller
     * 
     */
    virtual void OnTick();

    /**
     * @brief Retreives the current View
     * 
     * @return sf::View the view
     */
    virtual sf::View GetView();

  private:
    Entity* mEntity = nullptr;
    bool mEnableRotation = false;
    sf::View mView;
    sf::Vector2f mBounds;
    float mRadius;

    void updatePosNonRotating(sf::Vector2f worldBounds);
    void updatePosRotating(sf::Vector2f worldBounds);
  };
} // namespace game

#endif