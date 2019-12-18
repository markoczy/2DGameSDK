#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  class GAMESDK_DLL Renderer {
  public:
    Renderer(GameBase* game, sf::RenderWindow* window);
    void Run();

  protected:
    GameBase* mGame = nullptr;
    sf::RenderWindow* mWindow = nullptr;
    sf::Mutex* mRenderMutex = nullptr;

    void render();
  };

} // namespace game

#endif