#ifndef __CIRCLE_DYNAMIC_SHAPE_H__
#define __CIRCLE_DYNAMIC_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/DynamicShape.h>
#include <2DGameSDK/physics/shape/shapes/CircleShape.h>

namespace game {
  class GAMESDK_DLL CircleDynamicShape : public DynamicShape, public CircleShape {
  public:
    CircleDynamicShape(Game* game, float radius, cpVect offset = cpv(0, 0));
  };
} // namespace game

#endif