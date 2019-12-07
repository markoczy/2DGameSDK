#include <2DGameSDK/core/visual/AnimatedRenderStrategy.h>

namespace game {
  AnimatedRenderStrategy::AnimatedRenderStrategy(GameBase* game, std::map<int, sf::Texture*> animationStates, int startState) : RenderStrategy(game, true), mCurState(startState) {
    for(auto entry : animationStates) {
      mAnimationStates[entry.first] = sf::Sprite(*entry.second);
    }
  }

  AnimatedRenderStrategy::~AnimatedRenderStrategy() {}

  void AnimatedRenderStrategy::SetAnimState(int state) {
    mCurState = state;
  }

  void AnimatedRenderStrategy::SetSize(sf::Vector2f size) {
    for(auto entry : mAnimationStates) {
      SetSize(entry.first, size);
    }
  }

  void AnimatedRenderStrategy::SetSize(int state, sf::Vector2f size) {
    auto sprite = mAnimationStates[state];
    auto rect = sprite.getTextureRect();
    sprite.setScale(getGame()->GetPoseConverter()->GetVisualScale(sf::Vector2f(rect.width, rect.height), size));
  }

  void AnimatedRenderStrategy::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    target->draw(mAnimationStates[mCurState], states);
  }
} // namespace game
