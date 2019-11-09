#include <2DGameSDK/physics/shape/static/PolygonStaticShape.h>

namespace game {

  PolygonStaticShape::PolygonStaticShape(Game* game, std::vector<cpVect> vertices, bool isSensor) : Shape(ShapeType::Polygon, game), StaticShape(ShapeType::Polygon, game, isSensor), PolygonShape(game, vertices) {
  }
} // namespace game
