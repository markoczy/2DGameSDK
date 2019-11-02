#ifndef __PHYSICAL_ENTITY_H__
#define __PHYSICAL_ENTITY_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/Entity.h>

namespace game {

  class GAMESDK_DLL PhysicalEntity : public Entity {
  public:
    PhysicalEntity(int type, Game* game, bool isCollidable = false, float mass = 1, float moment = 1);

    ~PhysicalEntity();

    virtual bool IsTransformable();
    virtual bool IsCollidable();

    //? Outsource to Entity??
    virtual void SetMass(float mass);
    virtual void SetMoment(float moment);

    virtual void SetVelocity(cpVect velocity);
    virtual void SetForce(cpVect force);
    virtual void SetAngularVelocity(float angularVelocity);
    virtual void SetTorque(float torque);

  protected:
    bool mIsCollidable;
    cpBody* mBody = nullptr;
  };

} // namespace game

#endif