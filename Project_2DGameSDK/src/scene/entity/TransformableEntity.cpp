#include <2DGameSDK/scene/entity/TransformableEntity.h>

namespace game {

  TransformableEntity::TransformableEntity(int type, bool isCollidable) : Entity(type), mIsCollidable(isCollidable) {
  }

  TransformableEntity::~TransformableEntity() {}

  bool TransformableEntity::IsCollidable() {
    return mIsCollidable;
  }

  sf::Transform TransformableEntity::GetTransform() {
    return mTransform;
  }

  sf::Transform TransformableEntity::GetAccumulatedTransform() {
    return mAccTransform;
  }

  void TransformableEntity::SetGraphNode(game::SceneGraphNode* graphNode) {
    mGraphNode = graphNode;
    mGraphNode->OnEntityMoved(mAccTransform * mTransform);
  }

  void TransformableEntity::SetTransform(sf::Transform transform) {
    mTransform = transform;
    mGraphNode->OnEntityMoved(mAccTransform * mTransform);
  }

  void TransformableEntity::Transform(sf::Transform transform) {
    mTransform = mTransform * transform;
    mGraphNode->OnEntityMoved(mAccTransform * mTransform);
  }

  void TransformableEntity::OnParentTransformed(sf::Transform accumulated) {
    mAccTransform = accumulated;
  }

  void TransformableEntity::OnCollision(TransformableEntity*, sf::Vector2f) {}

} // namespace game