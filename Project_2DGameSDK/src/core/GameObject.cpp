#include <2DGameSDK/core/GameObject.h>

namespace game {
  int _entityCounter = 0;

  GameObject::GameObject(ObjectType objType, Game* game) : mObjectType(objType), mId(_entityCounter++), mGame(game) {
    // if(objType != ObjectType::Tile) {
    //   std::cout << "Init GameObject, objType: " << (int)objType << std::endl;
    // }
  }

  GameObject::~GameObject() {}

  int GameObject::GetId() {
    return mId;
  }

  ObjectType GameObject::GetObjectType() {
    return mObjectType;
  }

  Game* GameObject::getGame() {
    return mGame;
  }
} // namespace game