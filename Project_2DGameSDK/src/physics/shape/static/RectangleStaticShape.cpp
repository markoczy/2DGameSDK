#include <2DGameSDK/physics/shape/static/RectangleStaticShape.h>

namespace game {
  RectangleStaticShape::RectangleStaticShape(Game* game, float width, float height, bool isSensor) : Shape(ShapeType::Rectangle, game), StaticShape(ShapeType::Rectangle, game, isSensor), RectangleShape(game, width, height) {}

} // namespace game
