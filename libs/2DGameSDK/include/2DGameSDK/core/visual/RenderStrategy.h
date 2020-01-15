/**
 * @file RenderStrategy.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief RenderStrategy class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __RENDER_STRATEGY_H__
#define __RENDER_STRATEGY_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  /**
   * @brief Defines a generic Render Strategy
   * 
   */
  class GAMESDK_DLL RenderStrategy {
  public:
    /**
     * @brief Constructs a new Render Strategy
     * 
     * @param game the game
     * @param canRender wheter the strategy can be rendered
     */
    RenderStrategy(GameBase* game, bool canRender = false);

    /**
     * @brief Destroys the Render Strategy
     * 
     */
    virtual ~RenderStrategy();

    /**
     * @brief Returns wether rendering is enabled
     * 
     * @return bool is rendering enabled
     */
    virtual bool IsRenderEnabled();

    /**
     * @brief Renders the Object
     * 
     * @param target the render target
     * @param states the render states
     */
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states) = 0;

  protected:
    GameBase* getGame();
    bool mCanRender;

  private:
    GameBase* mGame;
  };

} // namespace game

#endif