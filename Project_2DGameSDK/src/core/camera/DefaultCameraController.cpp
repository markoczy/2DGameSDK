#include <2DGameSDK/core/camera/DefaultCameraController.h>

namespace game {
  DefaultCameraController::DefaultCameraController(GameBase* game) : CameraController(game) {}

  sf::Vector2f DefaultCameraController::GetBounds() {
    auto viewBounds = mView.getSize();
    auto conv = getGame()->GetPoseConverter();
    return sf::Vector2f(conv->GetPhysicalDimension(viewBounds.x), conv->GetPhysicalDimension(viewBounds.y));
  }

  void DefaultCameraController::SetZoom(float zoom) {
    auto windowSize = getGame()->GetWindow()->getSize();
    mView.setSize((float)windowSize.x / zoom, (float)windowSize.y / zoom);
  }

  void DefaultCameraController::SetCenter(sf::Vector2f center) {
    auto conv = getGame()->GetPoseConverter();
    mView.setCenter(conv->GetVisualPos(cpv(center.x, center.y)));
  }

  void DefaultCameraController::OnTick() {}

  sf::View DefaultCameraController::GetView() {
    return mView;
  }

} // namespace game
