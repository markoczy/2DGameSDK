#include <2DGameSDK/physics/shape/static/CircleStaticShape.h>

namespace game {
  CircleStaticShape::CircleStaticShape(Game* game, float radius, cpVect offset, bool isSensor) : Shape(ShapeType::Rectangle, game), StaticShape(ShapeType::Rectangle, game, isSensor), CircleShape(game, radius, offset) {}
} // namespace game
