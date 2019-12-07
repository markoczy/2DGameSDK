#ifndef __INVISIBLE_RENDER_STRATEGY_H__
#define __INVISIBLE_RENDER_STRATEGY_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  class GAMESDK_DLL InvisibleRenderStrategy : public RenderStrategy {
  public:
    InvisibleRenderStrategy(GameBase* game);
    virtual ~InvisibleRenderStrategy();

    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states);
  };

} // namespace game

#endif