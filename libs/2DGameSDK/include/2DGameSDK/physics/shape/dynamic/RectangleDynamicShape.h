#ifndef __RECTANGLE_DYNAMIC_SHAPE_H__
#define __RECTANGLE_DYNAMIC_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/RectangleShape.h>
#include <2DGameSDK/physics/shape/types/DynamicShape.h>

namespace game {
  class GAMESDK_DLL RectangleDynamicShape : public DynamicShape, public RectangleShape {
  public:
    RectangleDynamicShape(Game* game, float width, float height);
  };

} // namespace game

#endif