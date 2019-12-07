#ifndef __RENDER_STRATEGY_H__
#define __RENDER_STRATEGY_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  class GAMESDK_DLL RenderStrategy {
  public:
    RenderStrategy(GameBase* game, bool canRender = false);
    virtual ~RenderStrategy();

    virtual bool IsRenderEnabled();

    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states) = 0;

  protected:
    GameBase* getGame();
    bool mCanRender;

  private:
    GameBase* mGame;
  };

} // namespace game

#endif