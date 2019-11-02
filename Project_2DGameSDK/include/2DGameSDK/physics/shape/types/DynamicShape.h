#ifndef __DYNAMIC_SHAPE_H__
#define __DYNAMIC_SHAPE_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>

namespace game {
  class GAMESDK_DLL DynamicShape : public Shape {
  public:
    DynamicShape(ShapeType type, Game* game);

    void SetDensity(float density);

    void SetMass(float mass);

    void SetFriction(float friction);

    void SetElasticity(float elasticity);

  protected:
    float mDensity = 0;
    float mMass = 1;
    float mFriction = 0;
    float mElasticity = 0;

    virtual void initProperties(cpSpace* space, cpBody* body, cpShape* shape);
  };
} // namespace game

#endif