#ifndef __KINEMATIC_SHAPE_H__
#define __KINEMATIC_SHAPE_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>

namespace game {
  class GAMESDK_DLL KinematicShape : virtual public Shape {
  public:
    KinematicShape(ShapeType type, Game* game, bool isSensor = true);

    void SetFriction(float friction);

    void SetElasticity(float elasticity);

  protected:
    bool mIsSensor = false;
    float mFriction = 0;
    float mElasticity = 0;

    virtual void initProperties(cpSpace* space, cpBody* body, cpShape* shape);
  };
} // namespace game

#endif