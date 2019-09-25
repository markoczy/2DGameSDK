#include <2DGameSDK/scene/entity/TransformableEntity.h>

namespace game {
  // Forward declaration
  class SceneGraphNode {
  public:
    void OnEntityTransformed(sf::Transform accumulated);
  };

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
    mGraphNode->OnEntityTransformed(mAccTransform * mTransform);
  }

  void TransformableEntity::SetTransform(sf::Transform transform) {
    mTransform = transform;
    mFullTransform = mAccTransform * mTransform;
    if(mGraphNode != nullptr) mGraphNode->OnEntityTransformed(mFullTransform);
    onEntityTransformed();
  }

  void TransformableEntity::Transform(sf::Transform transform) {
    mTransform = mTransform * transform;
    mFullTransform = mAccTransform * mTransform;
    if(mGraphNode != nullptr) mGraphNode->OnEntityTransformed(mFullTransform);
    onEntityTransformed();
  }

  void TransformableEntity::OnTickEnded() {}

  void TransformableEntity::OnParentTransformed(sf::Transform accumulated) {
    mAccTransform = accumulated;
    mFullTransform = accumulated * mTransform;
    onEntityTransformed();
  }

  void TransformableEntity::OnCollision(TransformableEntity*, sf::Vector2f) {}

  void TransformableEntity::onEntityTransformed() {}

} // namespace game