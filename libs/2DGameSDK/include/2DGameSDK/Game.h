#ifndef __GAME_H__
#define __GAME_H__

#include "gamesdk_dll.h"
#include <SFML/Graphics.hpp>

namespace game {

  struct GAMESDK_DLL GameOptions {
    sf::Vector2i ScreenDim;
    int FramesPerSecond;
  };

  GAMESDK_DLL GameOptions DefaultOptions = GameOptions{
      sf::Vector2i(800, 600), 50};

  class GAMESDK_DLL Game {
  public:
    Game(GameOptions options = DefaultOptions);
    void Run();
    void Stop();
  };
} // namespace game

#endif