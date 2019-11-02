#include <2DGameSDK/physics/shape/sensor/RectangleSensorShape.h>

namespace game {
  RectangleSensorShape::RectangleSensorShape(Game* game, float width, float height) : Shape(ShapeType::Rectangle, game), SensorShape(ShapeType::Rectangle, game), RectangleShape(game, width, height) {}
} // namespace game
