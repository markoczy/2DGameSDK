#include <2DGameSDK/physics/shape/kinematic/RectangleKinematicShape.h>

namespace game {
  RectangleKinematicShape::RectangleKinematicShape(Game* game, float width, float height) : Shape(ShapeType::Rectangle, game), KinematicShape(ShapeType::Rectangle, game), RectangleShape(game, width, height) {}
} // namespace game
