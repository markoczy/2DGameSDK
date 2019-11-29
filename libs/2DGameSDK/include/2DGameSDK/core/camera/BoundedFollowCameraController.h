#ifndef __BOUNDED_FOLLOW_CAMERA_CONTROLLER_H__
#define __BOUNDED_FOLLOW_CAMERA_CONTROLLER_H__

#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/camera/CameraController.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/Entity.h>
#include <2DGameSDK/world/GameWorld.h>

namespace game {
  class GAMESDK_DLL BoundedFollowCameraController : public CameraController {
  public:
    BoundedFollowCameraController(GameBase* game, Entity* entity, bool enableRotation = false);

    virtual sf::Vector2f GetBounds();
    virtual void SetZoom(float zoom);

    virtual void SetCenter(sf::Vector2f center);

    virtual void OnTick();
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