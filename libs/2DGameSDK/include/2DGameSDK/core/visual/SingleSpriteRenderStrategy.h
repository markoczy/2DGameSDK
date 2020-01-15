/**
 * @file SingleSpriteRenderStrategy.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief SingleSpriteRenderStrategy class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __SINGLE_SPRITE_RENDER_STRATEGY_H__
#define __SINGLE_SPRITE_RENDER_STRATEGY_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  /**
   * @brief Defines a render strategy that is defined by a single texture
   * 
   */
  class GAMESDK_DLL SingleSpriteRenderStrategy : public RenderStrategy {
  public:
    /**
     * @brief Constructs a new Single Sprite Render Strategy
     * 
     * @param game the game
     * @param tex the texture
     */
    SingleSpriteRenderStrategy(GameBase* game, sf::Texture* tex);

    /**
     * @brief Destroys the Single Sprite Render Strategy
     * 
     */
    virtual ~SingleSpriteRenderStrategy();

    /**
     * @brief Retreives the current Sprite
     * 
     * @return sf::Sprite* the sprite
     */
    virtual sf::Sprite* GetSprite();

    /**
     * @brief Sets the Size
     * 
     * @param size the new size
     */
    virtual void SetSize(sf::Vector2f size);

    /**
     * @brief Renders the object
     * 
     * @param target the render target
     * @param states the render states
     */
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states);

  protected:
    sf::Sprite mSprite;
  };

} // namespace game

#endif