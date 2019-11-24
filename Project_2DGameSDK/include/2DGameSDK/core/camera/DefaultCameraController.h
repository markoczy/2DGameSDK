#ifndef __DEFAULT_CAMERA_CONTROLLER_H__
#define __DEFAULT_CAMERA_CONTROLLER_H__

#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/camera/CameraController.h>
#include <2DGameSDK/world/GameWorld.h>

namespace game {
  class DefaultCameraController : public CameraController {
  public:
    DefaultCameraController(GameBase* game);

    sf::Vector2f GetBounds();
    void SetZoom(float zoom);

    void SetCenter(sf::Vector2f center);

    virtual void OnTick() = 0;
    virtual sf::View GetView() = 0;

  private:
    sf::View mView;
    sf::Vector2f mBounds;
    sf::Vector2f mCenter;
  };
} // namespace game

#endif