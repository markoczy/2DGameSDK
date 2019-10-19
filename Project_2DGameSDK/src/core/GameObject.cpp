#include <2DGameSDK/core/GameObject.h>

namespace game {
  int _entityCounter = 0;

  GameObject::GameObject(int type, Game* game) : mType(type), mId(_entityCounter++), mGame(game) {}

  GameObject::~GameObject() {}

  int GameObject::GetType() {
    return mType;
  }

  int GameObject::GetId() {
    return mId;
  }

  int GameObject::GetZIndex() {
    return mZIndex;
  }

  void GameObject::SetZIndex(int zIndex) {
    mZIndex = zIndex;
  }

  Game* GameObject::getGame() {
    return mGame;
  }

  void GameObject::setType(int type) {
    mType = type;
  }
} // namespace game