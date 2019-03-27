#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/Graphics.hpp>

namespace game {

  struct GameOptions {
    sf::Vector2i ScreenDim;
    int FramesPerSecond;
  };

  GameOptions DefaultOptions = GameOptions{
      sf::Vector2i(800, 600), 50};

  class Game {
  public:
    Game(GameOptions options = DefaultOptions);
    void Run();
    void Stop();
  };
} // namespace game

#endif