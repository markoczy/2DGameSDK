/**
 * @file ExtendedSequenceRenderStrategy.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief ExtendedSequenceRenderStrategy
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __EXTENDED_SEQUENCE_RENDER_STRATEGY_H__
#define __EXTENDED_SEQUENCE_RENDER_STRATEGY_H__

#include <SFML/Graphics.hpp>
#include <map>

#include <2DGameSDK/core/visual/AnimatedRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  /**
   * @brief Improved AnimatedRenderStrategy that allows to define a sequence
   *        of Animation States
   * 
   */
  class GAMESDK_DLL ExtendedSequenceRenderStrategy : public AnimatedRenderStrategy {
    /**
     * @brief Constructs a new Extended Sequence Render Strategy
     * 
     * @param game the game
     * @param animationStates the animation states map
     * @param startState the start state
     */
    ExtendedSequenceRenderStrategy(GameBase* game, std::map<int, sf::Texture*> animationStates, int startState = constants::DEFAULT_ANIMATION_START);

    /**
     * @brief Defines a sequence to run
     * 
     * @param sequence the sequence to run
     * @param frames the frames per step
     * @param loop wether to loop the sequence
     */
    virtual void RunSequence(std::vector<int> sequence, int frames, bool loop = true);

    /**
     * @brief Stops at last element of the sequence (i.e. stops loop)
     * 
     */
    virtual void StopAtLast();

    /**
     * @brief Stops immediatly
     * 
     * @param newState 
     */
    virtual void StopNow(int newState);

    /**
     * @brief Renders the object
     * 
     * @param target the render target
     * @param states the render states
     */
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