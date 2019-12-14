#include <2DGameSDK/core/visual/SimpleSequenceRenderStrategy.h>

namespace game {

  SimpleSequenceRenderStrategy::SimpleSequenceRenderStrategy(GameBase* game, std::vector<sf::Texture*> sequence, int frames, int startAt, bool repeat) : RenderStrategy(game, true), mFrames(frames), mCurIdx(startAt), mRepeated(repeat) {
    mSequence = std::vector<sf::Sprite>(sequence.size());
    for(unsigned int i = 0; i < sequence.size(); i++) {
      auto sprite = sf::Sprite(*sequence[i]);
      auto rect = sprite.getLocalBounds();
      sprite.setOrigin(rect.width / 2, rect.height / 2);
      mSequence[i] = sprite;
    }
  }

  SimpleSequenceRenderStrategy::~SimpleSequenceRenderStrategy() {}

  bool SimpleSequenceRenderStrategy::IsFinished() {
    return mIsFinished;
  }

  void SimpleSequenceRenderStrategy::SetSize(int idx, sf::Vector2f size) {
    auto sprite = mSequence[idx];
    auto rect = sprite.getTextureRect();
    sprite.setScale(getGame()->GetPoseConverter()->GetVisualScale(sf::Vector2f(rect.width, rect.height), size));
  }

  void SimpleSequenceRenderStrategy::SetSize(sf::Vector2f size) {
    for(unsigned int i = 0; i < mSequence.size(); i++) {
      SetSize(i, size);
    }
  }

  void SimpleSequenceRenderStrategy::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    // not repeating and at end state
    if(mIsFinished) return;

    if(mCurFrame < mFrames) {
      mCurFrame++;
      return target->draw(mSequence[mCurIdx], states);
    }

    mCurFrame = 1;
    if((unsigned int)mCurIdx < mSequence.size() - 1) {
      mCurIdx++;
    } else if(mRepeated) {
      mCurIdx = 0;
    } else {
      mIsFinished = true;
    }

    return target->draw(mSequence[mCurIdx], states);
  }

} // namespace game