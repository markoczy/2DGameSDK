#include <2DGameSDK/physics/shape/dynamic/RectangleDynamicShape.h>

namespace game {

  RectangleDynamicShape::RectangleDynamicShape(Game* game, float width, float height) : RectangleShapeDefinition(game, width, height) {}

  void RectangleDynamicShape::initProperties(cpSpace* space, cpBody* body, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    cpShapeSetDensity(shape, mDensity);
    cpShapeSetMass(shape, mMass);
    cpShapeSetFriction(shape, mFriction);
    cpShapeSetElasticity(shape, mElasticity);
  }

  void RectangleDynamicShape::SetDensity(float density) {
    mDensity = density;
    auto shape = GetRefShape();
    if(shape != nullptr) {
      cpShapeSetDensity(shape, density);
    }
  }

  void RectangleDynamicShape::SetMass(float mass) {
    mMass = mass;
    auto shape = GetRefShape();
    if(shape != nullptr) {
      cpShapeSetMass(shape, mass);
    }
  }

  void RectangleDynamicShape::SetFriction(float friction) {
    mFriction = friction;
    auto shape = GetRefShape();
    if(shape != nullptr) {
      cpShapeSetFriction(shape, friction);
    }
  }

  void RectangleDynamicShape::SetElasticity(float elasticity) {
    mElasticity = elasticity;
    auto shape = GetRefShape();
    if(shape != nullptr) {
      cpShapeSetElasticity(shape, elasticity);
    }
  }

} // namespace game
