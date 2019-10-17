#include <2DGameSDK/core/GameObject.h>

namespace game {
  int _entityCounter = 0;

  GameObject::GameObject(int type, int zIndex) : mType(type), mId(_entityCounter++), mZIndex(zIndex) {}

  int GameObject::GetType() {
    return mType;
  }

  int GameObject::GetId() {
    return mId;
  }

  int GameObject::GetZIndex() {
    return mId;
  }

  GameObject::~GameObject() {}

} // namespace game