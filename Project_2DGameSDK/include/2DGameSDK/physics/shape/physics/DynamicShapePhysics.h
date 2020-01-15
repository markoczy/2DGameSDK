#ifndef __DYNAMIC_SHAPE_PHYSICS_H__
#define __DYNAMIC_SHAPE_PHYSICS_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/physics/ShapePhysics.h>

namespace game {
  class GAMESDK_DLL DynamicShapePhysics : public ShapePhysics<DynamicShapePhysics> {
  public:
    DynamicShapePhysics(float mass, float friction, float elasticity, bool useDensityForMass = false);

    virtual void InitProperties(cpSpace* space, cpBody* body, cpShape* shape);

    virtual DynamicShapePhysics* Copy();

  protected:
    float mMass = 0;
    float mFriction = 0;
    float mElasticity = 0;
    bool mUseDensity = false;
  };
} // namespace game

#endif