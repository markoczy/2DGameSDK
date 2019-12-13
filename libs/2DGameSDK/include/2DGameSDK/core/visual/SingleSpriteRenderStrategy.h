#ifndef __SINGLE_SPRITE_RENDER_STRATEGY_H__
#define __SINGLE_SPRITE_RENDER_STRATEGY_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  class GAMESDK_DLL SingleSpriteRenderStrategy : public RenderStrategy {
  public:
    SingleSpriteRenderStrategy(GameBase* game, sf::Texture* tex);
    virtual ~SingleSpriteRenderStrategy();

    virtual sf::Sprite* GetSprite();
    virtual void SetSize(sf::Vector2f size);
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states);

  protected:
    sf::Sprite mSprite;
  };

} // namespace game

#endif