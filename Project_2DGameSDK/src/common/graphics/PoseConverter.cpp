#include <2DGameSDK/common/graphics/PoseConverter.h>

namespace game {

  PoseConverter::PoseConverter(float worldWidth, float worldHeight, float meterPerPixel) : mWidth(worldWidth * meterPerPixel), mHeight(worldHeight * meterPerPixel), mPxToMeter(meterPerPixel) {}

  cpVect PoseConverter::GetPhysicalPos(sf::Vector2f visualPos) {
    return cpv(visualPos.x * mPxToMeter, (mHeight - visualPos.y) * mPxToMeter);
  }

  sf::Vector2f PoseConverter::GetVisualPos(cpVect physicalPos) {
    return sf::Vector2f(physicalPos.x / mPxToMeter, (mHeight - physicalPos.y) / mPxToMeter);
  }

  float PoseConverter::GetVisualAngle(float physicalAngle) {
    return -(180 * physicalAngle) / constants::PI;
  }

  float PoseConverter::GetPhysicalAngle(float visualAngle) {
    return -(constants::PI * visualAngle) / 180;
  }

  float PoseConverter::GetVisualDimension(float physicalDim) {
    return physicalDim / mPxToMeter;
  }

  float PoseConverter::GetPhysicalDimension(float visualDim) {
    return visualDim * mPxToMeter;
  }

  Pose<cpVect> PoseConverter::GetPhysicalPose(Pose<sf::Vector2f> visualPose) {
    return {
        GetPhysicalPos(visualPose.origin),
        GetPhysicalAngle(visualPose.angle)};
  }

  Pose<cpVect> PoseConverter::GetPhysicalPose(sf::Transform transform) {
    auto origin = transform.transformPoint(sf::Vector2f());
    auto xUnit = transform.transformPoint(sf::Vector2f(1, 0));
    auto dir = xUnit - origin;
    float angle = -atan2(dir.y, dir.x);
    return {
        cpv(origin.x, origin.y),
        angle};
  }

  Pose<sf::Vector2f> PoseConverter::GetVisualPose(Pose<cpVect> physicalPose) {
    return {
        GetVisualPos(physicalPose.origin),
        GetVisualAngle(physicalPose.angle)};
  }

  sf::Transform PoseConverter::GetVisualTransform(sf::Transform transform) {
    auto origin = transform.transformPoint(sf::Vector2f());
    auto xUnit = transform.transformPoint(sf::Vector2f(1, 0));
    auto visOrigin = GetVisualPos(cpv(origin.x, origin.y));
    auto visXUnit = GetVisualPos(cpv(xUnit.x, xUnit.y));
    auto visDir = visXUnit - visOrigin;
    float visAngle = GetVisualAngle(-atan2(visDir.y, visDir.x));
    return sf::Transform().translate(visOrigin).rotate(visAngle);
  }

  sf::Vector2f PoseConverter::GetVisualScale(sf::Vector2f txSize, sf::Vector2f physSize) {
    return sf::Vector2f((physSize.x / mPxToMeter) / txSize.x, (physSize.y / mPxToMeter) / txSize.y);
  }

} // namespace game
