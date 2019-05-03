#ifndef __GAME_H__
#define __GAME_H__

#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/core/GameState.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/EventController.h>
#include <2DGameSDK/event/observable/ObservableBase.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <iostream>
#include <thread>

namespace game {

  class GAMESDK_DLL Game {
  public:
    Game(GameOptions options, SceneGraph* scene, GameWorld* world, std::vector<ObservableBase*> events);
    ~Game();
    void Run();
    void Stop();

  private:
    void tick();
    void render();

    EventController mEventCtrl;
    GameOptions mOptions;
    GameState mState;
    sf::RenderWindow* mWindow;
    sf::View mView;
  };
} // namespace game

#endif