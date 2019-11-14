#ifndef __STATIC_SHAPE_DEFINITION_H__
#define __STATIC_SHAPE_DEFINITION_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>

namespace game {
  class GAMESDK_DLL StaticShapeDefinition : virtual public Shape {
  public:
    StaticShapeDefinition(Shape* shape, float friction, float elasticity, bool isSensor = true);

    virtual void InitProperties(cpSpace* space, cpBody* body, cpShape* shape);

  protected:
    Shape* mShape = nullptr;
    bool mIsSensor = false;
    float mFriction = 0;
    float mElasticity = 0;
  };
} // namespace game

#endif