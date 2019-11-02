#include <2DGameSDK/physics/shape/dynamic/RectangleDynamicShape.h>

namespace game {
  RectangleDynamicShape::RectangleDynamicShape(Game* game, float width, float height) : Shape(ShapeType::Rectangle, game), DynamicShape(ShapeType::Rectangle, game), RectangleShape(game, width, height) {}

} // namespace game
