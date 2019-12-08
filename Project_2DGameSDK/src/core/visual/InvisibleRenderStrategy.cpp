#include <2DGameSDK/core/visual/InvisibleRenderStrategy.h>

namespace game {
  InvisibleRenderStrategy::InvisibleRenderStrategy(GameBase* game) : RenderStrategy(game, false) {}

  InvisibleRenderStrategy::~InvisibleRenderStrategy() {}

  void InvisibleRenderStrategy::OnRender(sf::RenderTarget*, sf::RenderStates) {}
} // namespace game
