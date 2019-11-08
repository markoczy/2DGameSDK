#ifndef __PHYSICAL_ENTITY_H__
#define __PHYSICAL_ENTITY_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/types/DynamicShape.h>
#include <2DGameSDK/scene/entity/Entity.h>

namespace game {

  class GAMESDK_DLL PhysicalEntity : public Entity {
  public:
    PhysicalEntity(int type,
                   Game* game,
                   std::vector<DynamicShape*> shapes = std::vector<DynamicShape*>(),
                   bool isCollidable = false);

    ~PhysicalEntity();

    virtual bool IsKinematic();
    virtual bool IsCollidable();

    virtual void SetMass(float mass);
    virtual void SetMoment(float moment);

    virtual void SetVelocity(cpVect velocity);
    virtual void SetForce(cpVect force);
    virtual void SetAngularVelocity(float angularVelocity);
    virtual void SetTorque(float torque);

    virtual int OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb);

  protected:
    bool mIsCollidable;
    cpBody* mBody = nullptr;
    std::vector<DynamicShape*> mShapes;
  };

} // namespace game

#endif