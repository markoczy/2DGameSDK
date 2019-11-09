#ifndef __POLYGON_SENSOR_SHAPE_H__
#define __POLYGON_SENSOR_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/PolygonShape.h>
#include <2DGameSDK/physics/shape/types/SensorShape.h>

namespace game {
  class GAMESDK_DLL PolygonSensorShape : public SensorShape, public PolygonShape {
  public:
    PolygonSensorShape(Game* game, std::vector<cpVect> vertices);
  };

} // namespace game

#endif