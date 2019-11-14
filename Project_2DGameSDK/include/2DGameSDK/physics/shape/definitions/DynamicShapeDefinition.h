#ifndef __DYNAMIC_SHAPE_DEFINITION_H__
#define __DYNAMIC_SHAPE_DEFINITION_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/ShapeDefnition.h>

namespace game {
  class GAMESDK_DLL DynamicShapeDefinition : public ShapeDefinition {
  public:
    DynamicShapeDefinition(Shape* shape, float mass, float friction, float elasticity, bool useDensityForMass = false);

    virtual void InitProperties(cpSpace* space, cpBody* body, cpShape* shape);

  protected:
    Shape* mShape = nullptr;
    bool mUseDensity = false;
    float mMass = 0;
    float mFriction = 0;
    float mElasticity = 0;
  };
} // namespace game

#endif