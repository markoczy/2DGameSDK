#ifndef __RECTANGLE_SENSOR_SHAPE_H__
#define __RECTANGLE_SENSOR_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/RectangleShape.h>
#include <2DGameSDK/physics/shape/types/SensorShape.h>

namespace game {
  class GAMESDK_DLL RectangleSensorShape : public SensorShape, public RectangleShape {
  public:
    RectangleSensorShape(Game* game, float width, float height);
  };
} // namespace game

#endif