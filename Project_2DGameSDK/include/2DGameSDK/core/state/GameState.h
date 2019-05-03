#ifndef __GAME_STATE_H__
#define __GAME_STATE_H__

#include <2DGameSDK/scene/SceneGraph.h>
#include <2DGameSDK/world/GameWorld.h>
#include <SFML/Graphics.hpp>

namespace game {

  struct GameState {
    sf::View* View;
    SceneGraph* Scene;
    GameWorld* World;
  };

} // namespace game

#endif