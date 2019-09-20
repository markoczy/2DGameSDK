#include <2DGameSDK/scene/entity/TransformableEntity.h>

namespace game {

  TransformableEntity::TransformableEntity(int type, bool isCollidable) : Entity(type), mIsCollidable(isCollidable) {
  }

  TransformableEntity::~TransformableEntity() {}

  void TransformableEntity::SetGraphNode(game::SceneGraphNode* graphNode) {
    mGraphNode = graphNode;
  }

  bool TransformableEntity::IsCollidable() {
    return mIsCollidable;
  }

  void TransformableEntity::OnCollision(TransformableEntity*, sf::Vector2f) {}
} // namespace game