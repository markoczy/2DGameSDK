#include <2DGameSDK/scene/entity/Entity.h>

namespace game {
  int _entityCounter = 0;

  Entity::Entity(int type) : mType(type), mId(_entityCounter++) {}

  int Entity::GetType() {
    return mType;
  }

  int Entity::GetId() {
    return mId;
  }

  Entity::~Entity() {}

} // namespace game