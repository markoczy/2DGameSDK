#include <2DGameSDK/scene/entity/TransformableEntity.h>

namespace game {

  TransformableEntity::TransformableEntity(int type, bool isCollidable) : Entity(type), mIsCollidable(isCollidable) {
  }

  TransformableEntity::~TransformableEntity() {}

  void TransformableEntity::SetGraphNode(game::SceneGraphNode* graphNode) {
    mGraphNode = graphNode;
  }

  bool TransformableEntity::IsCollidable() {}

  void TransformableEntity::OnCollision(TransformableEntity* other) {}
} // namespace game