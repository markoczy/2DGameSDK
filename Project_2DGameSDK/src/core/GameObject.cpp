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

  void GameObject::OnTick() {}

  GameBase* GameObject::getGame() {
    return mGame;
  }

} // namespace game