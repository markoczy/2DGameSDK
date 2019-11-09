#include <2DGameSDK/event/observable/OnKeyPress.h>

using namespace std;

namespace game {
  OnKeyPress::OnKeyPress(sf::Keyboard::Key key) : mKey(key) {
  }

  tuple<bool, sf::Keyboard::Key> OnKeyPress::triggered() {
    bool pressed = sf::Keyboard::isKeyPressed(mKey);
    if(pressed) {
      LOGD("Keypress " << mKey << " triggered");
    }
    return tuple<bool, sf::Keyboard::Key>(pressed, mKey);
  }

} // namespace game
