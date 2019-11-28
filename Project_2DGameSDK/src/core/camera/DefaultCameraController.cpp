#include <2DGameSDK/core/camera/DefaultCameraController.h>

namespace game {
  DefaultCameraController::DefaultCameraController(GameBase* game) : CameraController(game) {
    SetZoom(game->GetOptions().InitialZoom);
  }

  sf::Vector2f DefaultCameraController::GetBounds() {
    return mBounds;
  }

  void DefaultCameraController::SetZoom(float zoom) {
    auto windowSize = getGame()->GetOptions().ScreenDim;
    float pxToM = getGame()->GetOptions().MeterPerPixel;
    float x = (float)windowSize.x / zoom;
    float y = (float)windowSize.y / zoom;
    mView.setSize(x, y);
    mBounds = sf::Vector2f(x * pxToM, y * pxToM);
  }

  void DefaultCameraController::SetCenter(sf::Vector2f center) {
    mCenter = center;
    mViewChanged = true;
  }

  void DefaultCameraController::OnTick() {
    if(mViewChanged) {
      auto conv = getGame()->GetPoseConverter();
      mView.setCenter(conv->GetVisualPos(cpv(mCenter.x, mCenter.y)));
      mViewChanged = false;
    }
  }

  sf::View DefaultCameraController::GetView() {
    return mView;
  }

  // void DefaultCameraController::updateBounds() {
  //   auto viewBounds = mView.getSize();
  //   auto conv = getGame()->GetPoseConverter();
  //   auto pxToM = getGame()->GetOptions().MeterPerPixel;
  //   mBounds = sf::Vector2f(viewBounds.x * pxToM, viewBounds.y * pxToM);
  // }

} // namespace game
