#include <2DGameSDK/physics/shape/dynamic/CircleDynamicShape.h>

namespace game {
  CircleDynamicShape::CircleDynamicShape(Game* game, float radius, cpVect offset) : Shape(ShapeType::Rectangle, game), DynamicShape(ShapeType::Rectangle, game), CircleShape(game, radius, offset) {}
} // namespace game
