#include <2DGameSDK/scene/SceneGraphNode.h>

using namespace sf;

namespace game {
  const Transform _ZERO_TRANSFORM = Transform();

  SceneGraphNode::SceneGraphNode(SceneGraph* graph, SceneGraphNode* parent, Entity* entity) : mGraph(graph), mParent(parent), mEntity(entity) {
    if(entity != nullptr) {
      entity->SetGraphNode(this);
    }
  }

  SceneGraphNode::~SceneGraphNode() {
    helpers::safeDelete(mEntity);
  }

  void SceneGraphNode::OnEntityDestroyed() {
    if(mParent != nullptr) mParent->RemoveChild(this);
  }

  void SceneGraphNode::OnEntityTransformed(sf::Transform accumulated) {
    for(auto iChild : mChildren) {
      auto ent = iChild->mEntity;
      if(ent != nullptr) {
        ent->OnParentTransformed(accumulated);
        auto parentTransform = ent->GetAccumulatedTransform() * ent->GetTransform();

        //TODO recursive overhead.. (stack??)
        iChild->OnEntityTransformed(parentTransform);
      }
    }
  }

  void SceneGraphNode::RemoveChild(SceneGraphNode* child) {
    auto it = std::find(mChildren.begin(), mChildren.end(), child);
    mChildren.erase(it);
  }
} // namespace game