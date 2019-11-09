#ifndef __CIRCLE_KINEMATIC_SHAPE_H__
#define __CIRCLE_KINEMATIC_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/KinematicShape.h>
#include <2DGameSDK/physics/shape/shapes/CircleShape.h>

namespace game {
  class GAMESDK_DLL CircleKinematicShape : public KinematicShape, public CircleShape {
  public:
    CircleKinematicShape(Game* game, float radius, cpVect offset = cpv(0, 0), bool isSensor = true);
  };
} // namespace game

#endif