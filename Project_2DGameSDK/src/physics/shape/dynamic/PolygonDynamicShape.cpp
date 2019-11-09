#include <2DGameSDK/physics/shape/dynamic/PolygonDynamicShape.h>

namespace game {

  PolygonDynamicShape::PolygonDynamicShape(Game* game, std::vector<cpVect> vertices) : Shape(ShapeType::Polygon, game), DynamicShape(ShapeType::Polygon, game), PolygonShape(game, vertices) {
  }
} // namespace game
