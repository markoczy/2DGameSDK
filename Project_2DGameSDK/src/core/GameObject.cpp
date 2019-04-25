#include "GameObject.h"

namespace game {

  GameObject::GameObject(const std::string& type) : mType(type) {}

  /* does nothing, meant to be overridden */
  void GameObject::Tick() {}

  /* does nothing, meant to be overridden */
  void GameObject::Render(sf::RenderTarget& target) {}

} // namespace game