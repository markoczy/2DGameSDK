#include <2DGameSDK/scene/entity/definitions/KinematicEntity.h>

namespace game {

  KinematicEntity::KinematicEntity(int type, Game* game, std::vector<KinematicShape*> shapes, bool isCollidable) : Entity(type, game), mShapes(shapes), mIsCollidable(isCollidable) {
    mBody = cpSpaceAddBody(game->GetPhysicalWorld(), cpBodyNewKinematic());
    cpBodySetUserData(mBody, this);

    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      shape->AttachToBody(space, mBody);
    }
  }

  KinematicEntity::~KinematicEntity() {}

  bool KinematicEntity::IsKinematic() {
    return true;
  }

  bool KinematicEntity::IsCollidable() {
    return mIsCollidable;
  }

  sf::Transform KinematicEntity::GetTransform() {
    return mTransform;
  }

  sf::Transform KinematicEntity::GetAccumulatedTransform() {
    return mAccTransform;
  }

  sf::Transform KinematicEntity::GetCombinedTransform() {
    return mCombinedTransform;
  }

  bool KinematicEntity::setTransform(sf::Transform transform) {
    mTransform = transform;
    mCombinedTransform = mAccTransform * mTransform;
    return true;
  }

  bool KinematicEntity::transform(sf::Transform transform) {
    mTransform = mTransform * transform;
    mCombinedTransform = mAccTransform * mTransform;
    return true;
  }

  bool KinematicEntity::setAccumulatedTransform(sf::Transform accumulated) {
    mAccTransform = accumulated;
    mCombinedTransform = mAccTransform * mTransform;
    return true;
  }

} // namespace game