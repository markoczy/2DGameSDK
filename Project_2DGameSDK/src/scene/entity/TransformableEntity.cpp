#include <2DGameSDK/scene/entity/TransformableEntity.h>

namespace game {

  TransformableEntity::TransformableEntity(int type, bool isCollidable) : Entity(type), mIsCollidable(isCollidable) {
  }

  TransformableEntity::~TransformableEntity() {}

  bool TransformableEntity::IsTransformable() {
    return true;
  }

  bool TransformableEntity::IsCollidable() {
    return mIsCollidable;
  }

  sf::Transform TransformableEntity::GetTransform() {
    return mTransform;
  }

  sf::Transform TransformableEntity::GetAccumulatedTransform() {
    return mAccTransform;
  }

  sf::Transform TransformableEntity::GetCombinedTransform() {
    return mCombinedTransform;
  }

  bool TransformableEntity::setTransform(sf::Transform transform) {
    mTransform = transform;
    mCombinedTransform = mAccTransform * mTransform;
    return true;
  }

  bool TransformableEntity::transform(sf::Transform transform) {
    mTransform = mTransform * transform;
    mCombinedTransform = mAccTransform * mTransform;
    return true;
  }

  bool TransformableEntity::setAccumulatedTransform(sf::Transform accumulated) {
    mAccTransform = accumulated;
    mCombinedTransform = mAccTransform * mTransform;
    return true;
  }

  void TransformableEntity::OnTickEnded() {}

  void TransformableEntity::OnCollision(Entity*, sf::Vector2f) {}

} // namespace game