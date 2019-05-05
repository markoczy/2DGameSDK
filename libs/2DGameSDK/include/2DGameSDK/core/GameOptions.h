#ifndef __GAME_OPTIONS_H__
#define __GAME_OPTIONS_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/System.hpp>

namespace game {

  struct GameOptions {
    std::string Title;
    sf::Vector2i ScreenDim;
    float InitialZoom;
    int FramesPerSecond;
  };

  //   GAMESDK_DLL GameOptions DefaultOptions = GameOptions{
  //       "Game", sf::Vector2i(800, 600), 50};
} // namespace game

#endif