#include <2DGameSDK/core/visual/SequencedRenderStrategy.h>

namespace game {
  SequencedRenderStrategy::SequencedRenderStrategy(GameBase* game, std::map<int, sf::Texture*> animationStates, int startState) : AnimatedRenderStrategy(game, animationStates, startState) {}

  void SequencedRenderStrategy::RunSequence(std::vector<int> sequence, int frames, bool loop) {
    mSequence = sequence;
    mFrames = frames;
    mLooping = loop;
    mRunning = true;
    mCurFrame = 0;
    mCurIdx = 0;
    SetAnimState(sequence[0]);
  }

  void SequencedRenderStrategy::StopAtLast() {
    mLooping = false;
  }

  void SequencedRenderStrategy::StopNow(int newState) {
    mRunning = false;
    SetAnimState(newState);
  }

  void SequencedRenderStrategy::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    if(!mRunning) return AnimatedRenderStrategy::OnRender(target, states);
    if(mCurFrame < mFrames) {
      mCurFrame++;
      return AnimatedRenderStrategy::OnRender(target, states);
    }

    mCurFrame = 0;
    if((unsigned int)mCurIdx < mSequence.size() - 1) {
      mCurIdx++;
    } else {
      if(mLooping) {
        mCurIdx = 0;
      } else {
        mRunning = false;
      }
    }
    SetAnimState(mSequence[mCurIdx]);
    mCurFrame++;
    return AnimatedRenderStrategy::OnRender(target, states);
  }
} // namespace game