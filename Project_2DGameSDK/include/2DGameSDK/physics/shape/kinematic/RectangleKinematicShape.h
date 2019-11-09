#ifndef __RECTANGLE_KINEMATIC_SHAPE_H__
#define __RECTANGLE_KINEMATIC_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/RectangleShape.h>
#include <2DGameSDK/physics/shape/types/KinematicShape.h>

namespace game {
  class GAMESDK_DLL RectangleKinematicShape : public KinematicShape, public RectangleShape {
  public:
    RectangleKinematicShape(Game* game, float width, float height);
  };
} // namespace game

#endif