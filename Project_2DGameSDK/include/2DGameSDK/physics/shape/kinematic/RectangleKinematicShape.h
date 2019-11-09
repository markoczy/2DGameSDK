#ifndef __RECTANGLE_KINEMATIC_SHAPE_H__
#define __RECTANGLE_KINEMATIC_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/KinematicShape.h>
#include <2DGameSDK/physics/shape/shapes/RectangleShape.h>

namespace game {
  class GAMESDK_DLL RectangleKinematicShape : public KinematicShape, public RectangleShape {
  public:
    RectangleKinematicShape(Game* game, float width, float height, bool isSensor = true);
  };
} // namespace game

#endif