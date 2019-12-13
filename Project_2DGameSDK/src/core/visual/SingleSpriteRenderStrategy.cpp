#include <2DGameSDK/core/visual/SingleSpriteRenderStrategy.h>

namespace game {

  SingleSpriteRenderStrategy::SingleSpriteRenderStrategy(GameBase* game, sf::Texture* tex) : RenderStrategy(game, true), mSprite(*tex) {
    auto rect = mSprite.getLocalBounds();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);
  }

  SingleSpriteRenderStrategy::~SingleSpriteRenderStrategy() {}

  sf::Sprite* SingleSpriteRenderStrategy::GetSprite() {
    return &mSprite;
  }

  void SingleSpriteRenderStrategy::SetSize(sf::Vector2f size) {
    auto rect = mSprite.getTextureRect();
    mSprite.setScale(getGame()->GetPoseConverter()->GetVisualScale(sf::Vector2f(rect.width, rect.height), size));
  }

  void SingleSpriteRenderStrategy::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    target->draw(mSprite, states);
  }
} // namespace game
