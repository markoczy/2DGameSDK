#include <2DGameSDK/core/visual/RenderStrategy.h>

namespace game {

  RenderStrategy::RenderStrategy(GameBase* game, bool canRender) : mGame(game), mCanRender(canRender) {}

  RenderStrategy::~RenderStrategy() {}

  bool RenderStrategy::IsRenderEnabled() {
    return mCanRender;
  }

  GameBase* RenderStrategy::getGame() {
    return mGame;
  }

} // namespace game
