#include <2DGameSDK/event/observable/OnKeyPress.h>

using namespace std;

namespace game {
  OnKeyPress::OnKeyPress(sf::Keyboard::Key key) : mKey(key) {
  }

  tuple<bool, EmptyEventData*> OnKeyPress::triggered() {
    bool pressed = sf::Keyboard::isKeyPressed(mKey);
    if(pressed) {
      LOGD("Keypress " << mKey << " triggered");
    }
    return tuple<bool, EmptyEventData*>(pressed, nullptr);
  }

} // namespace game
