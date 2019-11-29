#include <2DGameSDK/core/camera/BoundedFollowCameraController.h>

namespace game {

  BoundedFollowCameraController::BoundedFollowCameraController(GameBase* game, Entity* entity, bool enableRotation) : CameraController(game), mEntity(entity), mEnableRotation(enableRotation) {
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
    float xVis = x * pxToM;
    float yVis = y * pxToM;
    mBounds = sf::Vector2f(x * pxToM, y * pxToM);
    mRadius = sqrtf(xVis * xVis + yVis * yVis) / 2.0;
  }

  void BoundedFollowCameraController::SetCenter(sf::Vector2f) {
    LOGW("Unsupported: BoundedFollowCameraController::SetCenter");
  }

  void BoundedFollowCameraController::OnTick() {
    auto conv = getGame()->GetPoseConverter();
    auto worldVisBounds = getGame()->GetWorld()->GetBounds();
    auto worldBounds = sf::Vector2f(
        conv->GetPhysicalDimension(worldVisBounds.width),
        conv->GetPhysicalDimension(worldVisBounds.height));

    if(mEnableRotation) {
      updatePosRotating(worldBounds);
    } else {
      updatePosNonRotating(worldBounds);
    }
  }
  sf::View BoundedFollowCameraController::GetView() {
    return mView;
  }

  void BoundedFollowCameraController::updatePosNonRotating(sf::Vector2f worldBounds) {
    auto conv = getGame()->GetPoseConverter();
    auto center = mEntity->GetCombinedTransform().transformPoint(sf::Vector2f());
    if(center.x < mBounds.x / 2) {
      center.x = mBounds.x / 2;
    } else if(center.x > worldBounds.x - mBounds.x / 2) {
      center.x = worldBounds.x - mBounds.x / 2;
    }
    if(center.y < mBounds.y / 2) {
      center.y = mBounds.y / 2;
    } else if(center.y > worldBounds.y - mBounds.y / 2) {
      center.y = worldBounds.y - mBounds.y / 2;
    }

    mView.setCenter(conv->GetVisualPos(cpv(center.x, center.y)));
  }
  void BoundedFollowCameraController::updatePosRotating(sf::Vector2f worldBounds) {
    auto conv = getGame()->GetPoseConverter();
    auto pose = conv->GetPhysicalPose(mEntity->GetCombinedTransform());

    if(pose.origin.x < mRadius) {
      pose.origin.x = mRadius;
    } else if(pose.origin.x > worldBounds.x - mRadius) {
      pose.origin.x = worldBounds.x - mRadius;
    }

    if(pose.origin.y < mRadius) {
      pose.origin.y = mRadius;
    } else if(pose.origin.y > worldBounds.y - mRadius) {
      pose.origin.y = worldBounds.y - mRadius;
    }

    mView.setCenter(conv->GetVisualPos(cpv(pose.origin.x, pose.origin.y)));
    mView.setRotation(conv->GetVisualAngle(pose.angle));
  }
} // namespace game