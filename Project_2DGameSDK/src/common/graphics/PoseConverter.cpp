#include <2DGameSDK/common/graphics/PoseConverter.h>

namespace game {

  PoseConverter::PoseConverter(float worldWidth, float worldHeight) : mWidth(worldWidth), mHeight(worldHeight) {}

  cpVect PoseConverter::GetPhysicalPos(sf::Vector2f visualPos) {
    return cpv(visualPos.x, mHeight - visualPos.y);
  }

  sf::Vector2f PoseConverter::GetVisualPos(cpVect physicalPos) {
    return sf::Vector2f(physicalPos.x, mHeight - physicalPos.y);
  }

  float PoseConverter::GetVisualAngle(float physicalAngle) {
    return -(360 * physicalAngle) / 6.28;
  }

  float PoseConverter::GetPhysicalAngle(float visualAngle) {
    return -(6.28 * visualAngle) / 360;
  }

} // namespace game
