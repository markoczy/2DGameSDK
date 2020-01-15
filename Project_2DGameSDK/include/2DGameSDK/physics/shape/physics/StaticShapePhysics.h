#ifndef __STATIC_SHAPE_PHYSICS_H__
#define __STATIC_SHAPE_PHYSICS_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/physics/ShapePhysics.h>

namespace game {
  class GAMESDK_DLL StaticShapePhysics : public ShapePhysics<StaticShapePhysics> {
  public:
    StaticShapePhysics(float friction, float elasticity, bool isSensor = true);

    virtual void InitProperties(cpSpace* space, cpBody* body, cpShape* shape);

    virtual StaticShapePhysics* Copy();

  protected:
    float mFriction = 0;
    float mElasticity = 0;
    bool mIsSensor = false;
  };
} // namespace game

#endif