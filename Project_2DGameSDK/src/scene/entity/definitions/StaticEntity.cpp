#include <2DGameSDK/scene/entity/definitions/StaticEntity.h>

namespace game {
  StaticEntity::StaticEntity(int type, Game* game, std::vector<Shape*> shapes, bool isCollidable) : Entity(type, game), mIsCollidable(isCollidable), mShapes(shapes) {
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

  int StaticEntity::OnCollision(CollisionEventType, Entity*, cpArbiter*) {
    return 1;
  }
} // namespace game
