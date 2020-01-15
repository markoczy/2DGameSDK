#ifndef __DEFAULT_CAMERA_CONTROLLER_H__
#define __DEFAULT_CAMERA_CONTROLLER_H__

#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/camera/CameraController.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/world/GameWorld.h>

namespace game {
  class GAMESDK_DLL DefaultCameraController : public CameraController {
  public:
    /**
     * @brief Constructs a new Default Camera Controller
     * 
     * @param game 
     */
    DefaultCameraController(GameBase* game);

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

  protected:
    bool mViewChanged = false;
    sf::View mView;
    sf::Vector2f mBounds;
    sf::Vector2f mCenter;
  };
} // namespace game

#endif