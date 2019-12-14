#include <2DGameSDK/scene/entity/Entity.h>

namespace game {
  class SceneGraphNode {
  public:
    void OnEntityTransformed(sf::Transform accumulated);
    void OnEntityDestroyed();
  };

  Entity::Entity(int type, GameBase* game) : GameObject(ObjectType::Entity, game), mType(type) {
    game->GetStateManager()->AddVisualObject(this);
  }

  Entity::~Entity() {
    if(mGraphNode != nullptr) {
      mGraphNode->OnEntityDestroyed();
    }
  }

  bool Entity::IsKinematic() { return false; }

  bool Entity::IsCollidable() { return false; }

  int Entity::GetType() {
    return mType;
  }

  int Entity::GetZIndex() { return mZIndex; }

  sf::Transform Entity::GetTransform() { return sf::Transform::Identity; }

  sf::Transform Entity::GetAccumulatedTransform() { return sf::Transform::Identity; }

  sf::Transform Entity::GetCombinedTransform() { return sf::Transform::Identity; }

  void Entity::SetZIndex(int zIndex) {
    mZIndex = zIndex;
  }

  void Entity::SetTransform(sf::Transform transform) {
    if(this->setTransform(transform)) onEntityTransformed();
  }

  void Entity::SetGraphNode(SceneGraphNode* graphNode) {
    mGraphNode = graphNode;
    mGraphNode->OnEntityTransformed(GetCombinedTransform());
  }

  void Entity::Transform(sf::Transform transform) {
    if(this->transform(transform)) onEntityTransformed();
  }

  void Entity::OnParentTransformed(sf::Transform accumulated) {
    if(IsKinematic()) setAccumulatedTransform(accumulated);
  }

  void Entity::OnTickEnded() {}

  int Entity::OnCollision(CollisionEventType, Entity*, cpArbiter*) {
    return 0;
  }

  int Entity::OnWorldCollision(CollisionEventType, Tile*, cpArbiter*) {
    return 0;
  }

  int Entity::OnProjectileCollision(CollisionEventType, Projectile*, cpArbiter*) {
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
