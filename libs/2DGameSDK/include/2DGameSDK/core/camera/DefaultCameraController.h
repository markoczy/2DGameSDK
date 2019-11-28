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
    DefaultCameraController(GameBase* game);

    virtual sf::Vector2f GetBounds();
    virtual void SetZoom(float zoom);

    virtual void SetCenter(sf::Vector2f center);

    virtual void OnTick();
    virtual sf::View GetView();

  private:
    bool mViewChanged = false;
    sf::View mView;
    sf::Vector2f mBounds;
    sf::Vector2f mCenter;
  };
} // namespace game

#endif