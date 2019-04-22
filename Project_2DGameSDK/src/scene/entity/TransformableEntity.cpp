#include <2DGameSDK/scene/entity/TransformableEntity.h>

namespace game {

  TransformableEntity::TransformableEntity(int type) : Entity(type) {
  }

  TransformableEntity::~TransformableEntity() {}

  void TransformableEntity::SetGraphNode(game::SceneGraphNode* graphNode) {
    mGraphNode = graphNode;
  }
} // namespace game