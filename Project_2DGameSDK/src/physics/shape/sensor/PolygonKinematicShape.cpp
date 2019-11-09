#include <2DGameSDK/physics/shape/kinematic/PolygonKinematicShape.h>

namespace game {

  PolygonKinematicShape::PolygonKinematicShape(Game* game, std::vector<cpVect> vertices) : Shape(ShapeType::Polygon, game), KinematicShape(ShapeType::Polygon, game), PolygonShape(game, vertices) {
  }
} // namespace game
