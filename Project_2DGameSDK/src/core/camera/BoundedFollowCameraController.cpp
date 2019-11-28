#include <2DGameSDK/core/camera/BoundedFollowCameraController.h>

namespace game {

  BoundedFollowCameraController::BoundedFollowCameraController(GameBase* game, Entity* entity) : CameraController(game), mEntity(entity) {
    SetZoom(game->GetOptions().InitialZoom);
  }

  sf::Vector2f BoundedFollowCameraController::GetBounds() {
    return mBounds;
  }

  void BoundedFollowCameraController::SetZoom(float zoom) {
    auto windowSize = getGame()->GetOptions().ScreenDim;
    float pxToM = getGame()->GetOptions().MeterPerPixel;
    float x = (float)windowSize.x / zoom;
    float y = (float)windowSize.y / zoom;
    mView.setSize(x, y);
    mBounds = sf::Vector2f(x * pxToM, y * pxToM);
  }

  void BoundedFollowCameraController::SetCenter(sf::Vector2f) {
    LOGW("Unsupported: BoundedFollowCameraController::SetCenter");
  }

  void BoundedFollowCameraController::OnTick() {
    auto center = mEntity->GetCombinedTransform().transformPoint(sf::Vector2f());
    auto conv = getGame()->GetPoseConverter();
    mView.setCenter(conv->GetVisualPos(cpv(center.x, center.y)));
  }
  sf::View BoundedFollowCameraController::GetView() {
    return mView;
  }
} // namespace game