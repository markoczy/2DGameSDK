/**
 * @file InvisibleRenderStrategy.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief InvisibleRenderStrategy
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __INVISIBLE_RENDER_STRATEGY_H__
#define __INVISIBLE_RENDER_STRATEGY_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  /**
   * @brief Defines a render strategy where an object is not rendered at all
   * 
   */
  class GAMESDK_DLL InvisibleRenderStrategy : public RenderStrategy {
  public:
    /**
     * @brief Constructs a new Invisible Render Strategy
     * 
     * @param game the game
     */
    InvisibleRenderStrategy(GameBase* game);

    /**
     * @brief Destroys the Invisible Render Strategy
     * 
     */
    virtual ~InvisibleRenderStrategy();

    /**
     * @brief Renders the object
     * 
     * @param target the render target
     * @param states the render states
     */
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states);
  };

} // namespace game

#endif