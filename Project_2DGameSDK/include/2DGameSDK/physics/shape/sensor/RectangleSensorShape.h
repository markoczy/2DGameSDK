#ifndef __RECTANGLE_SENSOR_SHAPE_H__
#define __RECTANGLE_SENSOR_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/RectangleShapeDefinition.h>

namespace game {
  class GAMESDK_DLL RectangleSensorShape : public RectangleShapeDefinition {
  public:
    RectangleSensorShape(Game* game, float width, float height);

  protected:
    virtual void initProperties(cpSpace* space, cpBody* body, cpShape* shape);
  };
} // namespace game

#endif