#ifndef __RECTANGLE_STATIC_SHAPE_H__
#define __RECTANGLE_STATIC_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/StaticShape.h>
#include <2DGameSDK/physics/shape/shapes/RectangleShape.h>

namespace game {
  class GAMESDK_DLL RectangleStaticShape : public StaticShape, public RectangleShape {
  public:
    RectangleStaticShape(Game* game, float width, float height, bool isSensor = false);
  };

} // namespace game

#endif