#include <2DGameSDK/scene/SceneGraphNode.h>

using namespace sf;

namespace game {
  const Transform _ZERO_TRANSFORM = Transform();

  SceneGraphNode::SceneGraphNode(SceneGraphNode* parent, TransformableEntity* entity) : mParent(parent), mEntity(entity) {
    if(entity != nullptr) {
      entity->SetGraphNode(this);
    }
  }

  SceneGraphNode::~SceneGraphNode() {
    for(auto iChild : mChildren) {
      helpers::safeDelete(iChild);
    }
    helpers::safeDelete(mEntity);
  }

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

  void SceneGraphNode::Render(sf::RenderTarget* target, GameOptions* options, sf::RenderStates states) {
    // mRoot->Render(target, states);
    if(mEntity != nullptr) {
      mEntity->Render(target, states);
      states = RenderStates(states.transform * mEntity->GetTransformable()->getTransform());

      if(options->RenderAABB) {
        auto aabb = mEntity->GetAABB();
        auto rect = sf::RectangleShape(sf::Vector2f(aabb.width, aabb.height));
        rect.setPosition(aabb.left, aabb.top);
        rect.setOutlineColor(sf::Color::Magenta);
        rect.setOutlineThickness(1);
        rect.setFillColor(sf::Color::Transparent);
        target->draw(rect);
      }

      if(options->RenderCollisionMask) {
        auto collisionMask = mEntity->GetCollisionMask();
        if(collisionMask.size() > 0) {
          auto shape = sf::ConvexShape(collisionMask.size());
          for(int i = 0; i < collisionMask.size(); i++) {
            shape.setPoint(i, collisionMask[i]);
          }
          shape.setOutlineColor(sf::Color::Red);
          shape.setOutlineThickness(1);
          shape.setFillColor(sf::Color::Transparent);
          target->draw(shape);
        }
      }
    }
    for(auto iChild : mChildren) {
      iChild->Render(target, options, states);
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