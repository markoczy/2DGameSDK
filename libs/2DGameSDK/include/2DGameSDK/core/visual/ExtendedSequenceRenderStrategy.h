#ifndef __EXTENDED_SEQUENCE_RENDER_STRATEGY_H__
#define __EXTENDED_SEQUENCE_RENDER_STRATEGY_H__

#include <SFML/Graphics.hpp>
#include <map>

#include <2DGameSDK/core/visual/AnimatedRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  class GAMESDK_DLL ExtendedSequenceRenderStrategy : public AnimatedRenderStrategy {
    ExtendedSequenceRenderStrategy(GameBase* game, std::map<int, sf::Texture*> animationStates, int startState = constants::DEFAULT_ANIMATION_START);

    virtual void RunSequence(std::vector<int> sequence, int frames, bool loop = true);
    virtual void StopAtLast();
    virtual void StopNow(int newState);

    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states);

  protected:
    std::vector<int> mSequence;
    bool mLooping = false;
    bool mRunning = false;
    int mFrames = 1;
    int mCurFrame = 0;
    int mCurIdx = 0;
  };
} // namespace game

#endif