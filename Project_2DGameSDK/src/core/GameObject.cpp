#include <2DGameSDK/core/GameObject.h>

namespace game {
  int _entityCounter = 0;

  GameObject::GameObject(ObjectType objType, GameBase* game) : mObjectType(objType), mId(_entityCounter++), mGame(game) {
    mGame->GetStateManager()->AddObject(this);
  }

  GameObject::~GameObject() {}

  int GameObject::GetId() {
    return mId;
  }

  ObjectType GameObject::GetObjectType() {
    return mObjectType;
  }

  int GameObject::GetZIndex() {
    return mZIndex;
  }

  void GameObject::SetZIndex(int zIndex) {
    mZIndex = zIndex;
  }

  void GameObject::OnTick() {}

  void GameObject::OnRender(sf::RenderTarget*, sf::RenderStates) {}

  bool GameObject::SortByZOrder(GameObject* a, GameObject* b) {
    return a->GetZIndex() > b->GetZIndex();
  }

  GameBase* GameObject::getGame() {
    return mGame;
  }

} // namespace game