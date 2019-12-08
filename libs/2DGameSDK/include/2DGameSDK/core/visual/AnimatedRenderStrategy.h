#ifndef __ANIMATED_RENDER_STRATEGY_H__
#define __ANIMATED_RENDER_STRATEGY_H__

#include <map>

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  class GAMESDK_DLL AnimatedRenderStrategy : public RenderStrategy {
  public:
    AnimatedRenderStrategy(GameBase* game, std::map<int, sf::Texture*> animationStates, int startState = constants::DEFAULT_ANIMATION_START);
    virtual ~AnimatedRenderStrategy();

    virtual void SetAnimState(int state);

    virtual void SetSize(int state, sf::Vector2f size);

    virtual void SetSize(sf::Vector2f size);

    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states);

  protected:
    std::map<int, sf::Sprite> mAnimationStates;
    int mCurState;
  };
} // namespace game

#endif