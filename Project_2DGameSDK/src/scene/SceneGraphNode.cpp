#include <2DGameSDK/scene/SceneGraphNode.h>

using namespace sf;

namespace game {
  const Transform _ZERO_TRANSFORM = Transform();

  SceneGraphNode::SceneGraphNode(SceneGraphNode* parent, TransformableEntity* entity) : mParent(parent), mEntity(entity) {
    entity->SetGraphNode(this);
  }

  SceneGraphNode::~SceneGraphNode() {}

  SceneGraphNode* SceneGraphNode::AddChild(TransformableEntity* entity) {
    auto node = new SceneGraphNode(this, entity);
    mChildren.push_back(node);
    return node;
  }

  bool SceneGraphNode::IsRoot() {
    return mParent == nullptr;
  }

  void SceneGraphNode::Tick() {
    if(mEntity != nullptr) {
      mEntity->Tick();
    }
    for(auto iChild : mChildren) {
      iChild->Tick();
    }
  }

  sf::Transform SceneGraphNode::GetCurTransform() {
    if(mEntity == nullptr) {
      return _ZERO_TRANSFORM;
    }
    return mEntity->GetTransformable()->getTransform();
  }

  sf::Transform SceneGraphNode::GetAccumulatedTransform() {
    auto transform = Transform();
    auto cur = mParent;
    while(cur != nullptr) {
      transform *= cur->GetCurTransform();
      cur = cur->mParent;
    }
    return transform;
  }
} // namespace game