#include <2DGameSDK/event/observable/OnKeyPress.h>

namespace game {
  OnKeyPress::OnKeyPress(sf::Keyboard::Key key) : mKey(key) {
  }

  Observable<EmptyEventData>::TriggerData OnKeyPress::triggered() {
    return TriggerData{
        sf::Keyboard::isKeyPressed(mKey),
        nullptr};
  }

} // namespace game
