#include <2DGameSDK/scene/entity/definitions/KinematicEntity.h>

namespace game {

  KinematicEntity::KinematicEntity(int type, Game* game, std::vector<Shape*> shapes, bool isCollidable) : Entity(type, game), mShapes(shapes), mIsCollidable(isCollidable) {
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
    auto origin = transform.transformPoint(sf::Vector2f());
    auto xUnit = transform.transformPoint(sf::Vector2f(1, 0));
    auto dir = xUnit - origin;
    float angle = atan2(dir.y, dir.x);
    float visAngle = (360 * angle) / 6.28;
    auto newT = sf::Transform().translate(origin.x, -origin.y).rotate(visAngle);

    mTransform = mTransform * newT;
    mCombinedTransform = mAccTransform * mTransform;
    return true;
  }

  bool KinematicEntity::setAccumulatedTransform(sf::Transform accumulated) {
    mAccTransform = accumulated;
    mCombinedTransform = mAccTransform * mTransform;
    return true;
  }

} // namespace game