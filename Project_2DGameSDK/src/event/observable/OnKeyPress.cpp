#include <2DGameSDK/event/observable/OnKeyPress.h>

namespace game {
  OnKeyPress::OnKeyPress(sf::Keyboard::Key key) : mKey(key) {
  }

  EmptyEventData* OnKeyPress::triggered(bool* trigger) {
    auto triggered = sf::Keyboard::isKeyPressed(mKey);
    trigger = &triggered;
    return nullptr;
  }

} // namespace game
