#ifndef __POLYGON_SENSOR_SHAPE_H__
#define __POLYGON_SENSOR_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/PolygonShapeDefinition.h>

namespace game {
  class GAMESDK_DLL PolygonSensorShape : public PolygonShapeDefinition {
  public:
    PolygonSensorShape(Game* game, std::vector<cpVect> vertices);

  protected:
    virtual void initProperties(cpSpace* space, cpBody* body, cpShape* shape);
  };

} // namespace game

#endif