#include <2DGameSDK/common/graphics/PoseConverter.h>

namespace game {

  PoseConverter::PoseConverter(float worldWidth, float worldHeight, float meterPerPixel) : mWidth(worldWidth), mHeight(worldHeight), mPxToMeter(meterPerPixel) {}

  cpVect PoseConverter::GetPhysicalPos(sf::Vector2f visualPos) {
    return cpv(visualPos.x * mPxToMeter, (mHeight - visualPos.y) * mPxToMeter);
  }

  sf::Vector2f PoseConverter::GetVisualPos(cpVect physicalPos) {
    return sf::Vector2f(physicalPos.x / mPxToMeter, (mHeight - physicalPos.y) / mPxToMeter);
  }

  float PoseConverter::GetVisualAngle(float physicalAngle) {
    return -(360 * physicalAngle) / 6.28;
  }

  float PoseConverter::GetPhysicalAngle(float visualAngle) {
    return -(6.28 * visualAngle) / 360;
  }

  float PoseConverter::GetVisualDimension(float physicalDim) {
    return physicalDim / mPxToMeter;
  }

  float PoseConverter::GetPhysicalDimension(float visualDim) {
    return visualDim * mPxToMeter;
  }

} // namespace game
