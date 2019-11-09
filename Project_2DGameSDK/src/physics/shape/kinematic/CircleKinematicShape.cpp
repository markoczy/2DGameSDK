#include <2DGameSDK/physics/shape/kinematic/CircleKinematicShape.h>

namespace game {
  CircleKinematicShape::CircleKinematicShape(Game* game, float radius, cpVect offset, bool isSensor) : Shape(ShapeType::Rectangle, game), KinematicShape(ShapeType::Rectangle, game, isSensor), CircleShape(game, radius, offset) {}
} // namespace game
