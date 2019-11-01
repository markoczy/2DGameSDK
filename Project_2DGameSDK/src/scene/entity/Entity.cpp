#include <2DGameSDK/scene/entity/Entity.h>

namespace game {
  class SceneGraphNode {
  public:
    void OnEntityTransformed(sf::Transform accumulated);
  };

  Entity::Entity(int type, Game* game) : GameObject(type, game) {
  }

  Entity::~Entity() {}

  bool Entity::IsTransformable() { return false; }

  bool Entity::IsCollidable() { return false; }

  sf::Transform Entity::GetTransform() { return sf::Transform::Identity; }

  sf::Transform Entity::GetAccumulatedTransform() { return sf::Transform::Identity; }

  sf::Transform Entity::GetCombinedTransform() { return sf::Transform::Identity; }

  void Entity::SetTransform(sf::Transform transform) {
    if(IsTransformable() && this->setTransform(transform)) onEntityTransformed();
  }

  void Entity::SetGraphNode(SceneGraphNode* graphNode) {
    mGraphNode = graphNode;
    mGraphNode->OnEntityTransformed(GetCombinedTransform());
  }

  void Entity::Transform(sf::Transform transform) {
    if(IsTransformable() && this->transform(transform)) onEntityTransformed();
  }

  void Entity::OnParentTransformed(sf::Transform accumulated) {
    if(IsTransformable()) setAccumulatedTransform(accumulated);
  }

  void Entity::OnTickEnded() {}

  int Entity::OnCollision(CollisionEventType type, Entity* other, cpArbiter* arb) {
    return 0;
  }

  bool Entity::setTransform(sf::Transform) { return false; }
  bool Entity::transform(sf::Transform) { return false; }
  bool Entity::setAccumulatedTransform(sf::Transform) { return false; }

  void Entity::onEntityTransformed() {
    if(mGraphNode != nullptr) {
      mGraphNode->OnEntityTransformed(GetCombinedTransform());
    }
  }
} // namespace game
