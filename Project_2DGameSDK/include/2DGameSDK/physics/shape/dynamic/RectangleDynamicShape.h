#ifndef __RECTANGLE_DYNAMIC_SHAPE_H__
#define __RECTANGLE_DYNAMIC_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/RectangleShapeDefinition.h>

namespace game {
  class GAMESDK_DLL RectangleDynamicShape : public RectangleShapeDefinition {
  public:
    RectangleDynamicShape(Game* game, float width, float height);

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