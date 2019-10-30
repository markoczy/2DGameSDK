#ifndef __SENSOR_SHAPE_PROPERTIES_H__
#define __SENSOR_SHAPE_PROPERTIES_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/Shape.h>

namespace game {

  class GAMESDK_DLL SensorShapeProperties : public Shape {
    virtual void initProperties(cpSpace* space, cpBody* body, cpShape* shape);
  };

} // namespace game

#endif