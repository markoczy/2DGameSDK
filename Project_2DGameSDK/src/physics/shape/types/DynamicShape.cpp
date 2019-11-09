#include <2DGameSDK/physics/shape/types/DynamicShape.h>

namespace game {
  DynamicShape::DynamicShape(ShapeType type, Game* game) : Shape(type, game) {}

  void DynamicShape::initProperties(cpSpace*, cpBody*, cpShape* shape) {
    cpShapeSetCollisionType(shape, CollisionType::Default);
    if(mDensity != 0) cpShapeSetDensity(shape, mDensity);
    if(mMass != 0) cpShapeSetMass(shape, mMass);
    if(mFriction != 0) cpShapeSetFriction(shape, mFriction);
    if(mElasticity != 0) cpShapeSetElasticity(shape, mElasticity);
  }

  void DynamicShape::SetDensity(float density) {
    mDensity = density;
    auto shape = GetRefShape();
    if(shape != nullptr) {
      cpShapeSetDensity(shape, density);
    }
  }

  void DynamicShape::SetMass(float mass) {
    mMass = mass;
    auto shape = GetRefShape();
    if(shape != nullptr) {
      cpShapeSetMass(shape, mass);
    }
  }

  void DynamicShape::SetFriction(float friction) {
    mFriction = friction;
    auto shape = GetRefShape();
    if(shape != nullptr) {
      cpShapeSetFriction(shape, friction);
    }
  }

  void DynamicShape::SetElasticity(float elasticity) {
    mElasticity = elasticity;
    auto shape = GetRefShape();
    if(shape != nullptr) {
      cpShapeSetElasticity(shape, elasticity);
    }
  }
} // namespace game
