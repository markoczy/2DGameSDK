#ifndef __SIMPLE_SEQUENCE_RENDER_STRATEGY_H__
#define __SIMPLE_SEQUENCE_RENDER_STRATEGY_H__

#include <vector>

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  class GAMESDK_DLL SimpleSequenceRenderStrategy : public RenderStrategy {
  public:
    SimpleSequenceRenderStrategy(GameBase* game, std::vector<sf::Texture*> sequence, int frames = 1, int startAt = 0, bool repeat = true);

    virtual ~SimpleSequenceRenderStrategy();

    virtual bool IsFinished();

    virtual void SetSize(int idx, sf::Vector2f size);

    virtual void SetSize(sf::Vector2f size);

    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states);

  protected:
    int mFrames = 1;
    int mCurIdx = 0;
    bool mRepeated = true;
    std::vector<sf::Sprite> mSequence;
    int mCurFrame = 0;
    bool mIsFinished = false;
  };
} // namespace game

#endif