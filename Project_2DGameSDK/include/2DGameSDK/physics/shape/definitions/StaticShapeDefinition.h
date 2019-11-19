#ifndef __STATIC_SHAPE_DEFINITION_H__
#define __STATIC_SHAPE_DEFINITION_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/definitions/ShapeDefinition.h>

namespace game {
  class GAMESDK_DLL StaticShapeDefinition : public ShapeDefinition<StaticShapeDefinition> {
  public:
    StaticShapeDefinition(float friction, float elasticity, bool isSensor = true);

    virtual void InitProperties(cpSpace* space, cpBody* body, cpShape* shape);

    virtual StaticShapeDefinition* Copy();

  protected:
    float mFriction = 0;
    float mElasticity = 0;
    bool mIsSensor = false;
  };
} // namespace game

#endif