#ifndef __CIRCLE_KINEMATIC_SHAPE_H__
#define __CIRCLE_KINEMATIC_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/StaticShape.h>
#include <2DGameSDK/physics/shape/shapes/CircleShape.h>

namespace game {
  class GAMESDK_DLL CircleStaticShape : public StaticShape, public CircleShape {
  public:
    CircleStaticShape(Game* game, float radius, cpVect offset = cpv(0, 0), bool isSensor = false);
  };
} // namespace game

#endif