#ifndef __ON_KEY_PRESS_H__
#define __ON_KEY_PRESS_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/data/EmptyEventData.h>
#include <2DGameSDK/event/observable/Observable.h>
#include <SFML/Window.hpp>
#include <tuple>

namespace game {

  class GAMESDK_DLL OnKeyPress : public Observable<EmptyEventData> {
  public:
    OnKeyPress(sf::Keyboard::Key key);

  private:
    sf::Keyboard::Key mKey;

    virtual std::tuple<bool, EmptyEventData*> triggered();
  };
} // namespace game

#endif