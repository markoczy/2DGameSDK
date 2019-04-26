#ifndef __GAME_OPTIONS_H__
#define __GAME_OPTIONS_H__

#include "gamesdk_dll.h"
#include <SFML/System.hpp>

namespace game {

  struct GAMESDK_DLL GameOptions {
    std::string Title;
    sf::Vector2i ScreenDim;
    int FramesPerSecond;
  };

  //   GAMESDK_DLL GameOptions DefaultOptions = GameOptions{
  //       "Game", sf::Vector2i(800, 600), 50};
} // namespace game

#endif