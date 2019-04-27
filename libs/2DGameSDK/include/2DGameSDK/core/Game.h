#ifndef __GAME_H__
#define __GAME_H__

#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <iostream>
#include <thread>

namespace game {

  class GAMESDK_DLL Game {
  public:
    Game(GameOptions options);
    ~Game();
    void Run();
    void Stop();

  private:
    void tick();
    void render();

    GameOptions mOptions;
    sf::RenderWindow* mWindow;
    sf::View mView;
  };
} // namespace game

#endif