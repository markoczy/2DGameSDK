#ifndef __KINEMATIC_SHAPE_DEFINITION_H__
#define __KINEMATIC_SHAPE_DEFINITION_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/definitions/ShapeDefinition.h>

namespace game {
  class GAMESDK_DLL KinematicShapeDefinition : public ShapeDefinition {
  public:
    KinematicShapeDefinition(float friction, float elasticity, bool isSensor = true);

    virtual void InitProperties(cpSpace* space, cpBody* body, cpShape* shape);

  protected:
    float mFriction = 0;
    float mElasticity = 0;
    bool mIsSensor = false;
  };
} // namespace game

#endif