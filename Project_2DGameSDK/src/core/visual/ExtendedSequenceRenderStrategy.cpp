#include <2DGameSDK/core/visual/ExtendedSequenceRenderStrategy.h>

namespace game {
  ExtendedSequenceRenderStrategy::ExtendedSequenceRenderStrategy(GameBase* game, std::map<int, sf::Texture*> animationStates, int startState) : AnimatedRenderStrategy(game, animationStates, startState) {}

  void ExtendedSequenceRenderStrategy::RunSequence(std::vector<int> sequence, int frames, bool loop) {
    mSequence = sequence;
    mFrames = frames;
    mLooping = loop;
    mRunning = true;
    mCurFrame = 0;
    mCurIdx = 0;
    SetAnimState(sequence[0]);
  }

  void ExtendedSequenceRenderStrategy::StopAtLast() {
    mLooping = false;
  }

  void ExtendedSequenceRenderStrategy::StopNow(int newState) {
    mRunning = false;
    SetAnimState(newState);
  }

  void ExtendedSequenceRenderStrategy::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
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