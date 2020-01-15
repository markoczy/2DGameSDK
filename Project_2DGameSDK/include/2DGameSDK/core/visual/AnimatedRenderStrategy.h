/**
 * @file AnimatedRenderStrategy.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief AnimatedRenderStrategy class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
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
  /**
   * @brief Defines a render strategy where an object is rendered one of 
   *        multiple textures depending on the current animation state
   * 
   */
  class GAMESDK_DLL AnimatedRenderStrategy : public RenderStrategy {
  public:
    /**
     * @brief Constructs a new Animated Render Strategy
     * 
     * @param game the game
     * @param animationStates the animation states map
     * @param startState the starting animation state
     */
    AnimatedRenderStrategy(GameBase* game, std::map<int, sf::Texture*> animationStates, int startState = constants::DEFAULT_ANIMATION_START);

    /**
     * @brief Destroys the Animated Render Strategy
     * 
     */
    virtual ~AnimatedRenderStrategy();

    /**
     * @brief Sets the Animation State
     * 
     * @param state the new animation state
     */
    virtual void SetAnimState(int state);

    /**
     * @brief Sets the Size for a given state
     * 
     * @param state the state
     * @param size the new size
     */
    virtual void SetSize(int state, sf::Vector2f size);

    /**
     * @brief Sets the Size for all states
     * 
     * @param size the new size
     */
    virtual void SetSize(sf::Vector2f size);

    /**
     * @brief Renders the object
     * 
     * @param target 
     * @param states 
     */
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states);

  protected:
    std::map<int, sf::Sprite> mAnimationStates;
    int mCurState;
  };
} // namespace game

#endif