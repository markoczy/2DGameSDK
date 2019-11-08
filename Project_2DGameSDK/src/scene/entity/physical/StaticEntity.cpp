#include <2DGameSDK/scene/entity/physical/StaticEntity.h>

namespace game {
  StaticEntity::StaticEntity(int type, Game* game, std::vector<Shape*> shapes, bool isCollidable) : Entity(type, game), mShapes(shapes), mIsCollidable(isCollidable) {
    mBody = cpSpaceAddBody(game->GetPhysicalWorld(), cpBodyNewStatic());
    cpBodySetUserData(mBody, this);

    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      shape->AttachToBody(space, mBody);
    }
  }

  StaticEntity::~StaticEntity() {}

  bool StaticEntity::IsKinematic() { return false; }

  bool StaticEntity::IsCollidable() { return mIsCollidable; }

  int StaticEntity::OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb) {
    return 1;
  }
} // namespace game
