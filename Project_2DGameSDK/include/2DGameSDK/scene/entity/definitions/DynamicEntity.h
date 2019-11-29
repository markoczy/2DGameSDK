#ifndef __DYNAMIC_ENTITY_H__
#define __DYNAMIC_ENTITY_H__

#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/graphics/GraphicTools.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionTarget.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/DynamicShapeDefinition.h>
#include <2DGameSDK/scene/entity/Entity.h>

namespace game {

  class GAMESDK_DLL DynamicEntity : public Entity {
  public:
    DynamicEntity(int type,
                  GameBase* game,
                  std::vector<Shape<DynamicShapeDefinition>*> shapes = std::vector<Shape<DynamicShapeDefinition>*>(),
                  bool isCollidable = false);

    ~DynamicEntity();

    virtual sf::Transform GetTransform();
    virtual sf::Transform GetAccumulatedTransform();
    virtual sf::Transform GetCombinedTransform();

    virtual bool IsKinematic();
    virtual bool IsCollidable();

    virtual void SetMass(float mass);
    virtual void SetMoment(float moment);

    virtual void SetVelocity(cpVect velocity);
    virtual void SetForce(cpVect force);
    virtual void SetAngularVelocity(float angularVelocity);
    virtual void SetTorque(float torque);

    virtual int OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb);
    virtual int OnWorldCollision(CollisionEventType type, Tile* tile, cpArbiter* arb);

  protected:
    bool mIsCollidable;
    std::vector<Shape<DynamicShapeDefinition>*> mShapes;
    cpBody* mBody = nullptr;

    virtual bool setTransform(sf::Transform transform);
  };

} // namespace game

#endif