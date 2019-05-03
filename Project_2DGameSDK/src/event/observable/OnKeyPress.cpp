#include <2DGameSDK/event/observable/OnKeyPress.h>

using namespace std;

namespace game {
  OnKeyPress::OnKeyPress(sf::Keyboard::Key key) : mKey(key) {
  }

  tuple<bool, EmptyEventData*> OnKeyPress::triggered() {
    return make_tuple<bool, EmptyEventData*>(sf::Keyboard::isKeyPressed(mKey), nullptr);
  }

} // namespace game
