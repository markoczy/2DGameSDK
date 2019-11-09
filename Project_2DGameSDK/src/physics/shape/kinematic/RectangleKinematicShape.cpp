#include <2DGameSDK/physics/shape/kinematic/RectangleKinematicShape.h>

namespace game {
  RectangleKinematicShape::RectangleKinematicShape(Game* game, float width, float height, bool isSensor) : Shape(ShapeType::Rectangle, game), KinematicShape(ShapeType::Rectangle, game, isSensor), RectangleShape(game, width, height) {}
} // namespace game
