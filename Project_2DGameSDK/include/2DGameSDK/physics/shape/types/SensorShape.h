#ifndef __SENSOR_SHAPE_H__
#define __SENSOR_SHAPE_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>

namespace game {
  class GAMESDK_DLL SensorShape : public Shape {
  public:
    SensorShape(ShapeType type, Game* game);

  protected:
    virtual void initProperties(cpSpace* space, cpBody* body, cpShape* shape);
  };
} // namespace game

#endif