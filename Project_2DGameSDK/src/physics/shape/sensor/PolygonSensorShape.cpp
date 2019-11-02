#include <2DGameSDK/physics/shape/sensor/PolygonSensorShape.h>

namespace game {

  PolygonSensorShape::PolygonSensorShape(Game* game, std::vector<cpVect> vertices) : Shape(ShapeType::Polygon, game), SensorShape(ShapeType::Polygon, game), PolygonShape(game, vertices) {
  }
} // namespace game
