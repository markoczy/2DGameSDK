#include <2DGameSDK/physics/shape/kinematic/PolygonKinematicShape.h>

namespace game {

  PolygonKinematicShape::PolygonKinematicShape(Game* game, std::vector<cpVect> vertices, bool isSensor) : Shape(ShapeType::Polygon, game), KinematicShape(ShapeType::Polygon, game, isSensor), PolygonShape(game, vertices) {
  }
} // namespace game
