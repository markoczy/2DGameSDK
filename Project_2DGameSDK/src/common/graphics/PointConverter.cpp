#include <2DGameSDK/common/graphics/PointConverter.h>

namespace game {

  PointConverter::PointConverter(float worldWidth, float worldHeight) : mWidth(worldWidth), mHeight(worldHeight) {}

  cpVect PointConverter::GetPhysicalPos(sf::Vector2f visualPos) {
    return cpv(visualPos.x, mHeight - visualPos.y);
  }

  sf::Vector2f PointConverter::GetVisualPos(cpVect physicalPos) {
    return sf::Vector2f(physicalPos.x, mHeight - physicalPos.y);
  }

} // namespace game
