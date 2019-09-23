#include <2DGameSDK/scene/SceneGraphNode.h>

using namespace sf;

namespace game {
  const Transform _ZERO_TRANSFORM = Transform();

  SceneGraphNode::SceneGraphNode(SceneGraph* graph, SceneGraphNode* parent, TransformableEntity* entity) : mGraph(graph), mParent(parent), mEntity(entity) {
    if(entity != nullptr) {
      entity->SetGraphNode(this);
    }
  }

  SceneGraphNode::~SceneGraphNode() {
    helpers::safeDelete(mEntity);
  }

  void SceneGraphNode::OnEntityTransformed(sf::Transform accumulated) {
    for(auto iChild : mChildren) {
      auto ent = iChild->mEntity;
      if(ent != nullptr) {
        ent->OnParentTransformed(accumulated);
        auto parentTransform = ent->GetAccumulatedTransform() * ent->GetTransform();

        //TODO recursive overhead..
        iChild->OnEntityTransformed(parentTransform);
      }
    }
  }
  // sf::Transform SceneGraphNode::GetCurTransform() {
  //   if(mEntity == nullptr) {
  //     return _ZERO_TRANSFORM;
  //   }
  //   return mEntity->GetTransformable()->getTransform();
  // }

  // sf::Transform SceneGraphNode::GetAccumulatedTransform() {
  //   auto transform = Transform();
  //   auto cur = mParent;
  //   while(cur != nullptr) {
  //     transform *= cur->GetCurTransform();
  //     cur = cur->mParent;
  //   }
  //   return transform;
  // }
} // namespace game