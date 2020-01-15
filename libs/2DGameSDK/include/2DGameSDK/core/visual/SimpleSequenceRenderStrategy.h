/**
 * @file SimpleSequenceRenderStrategy.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief SimpleSequenceRenderStrategy
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
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
  /**
   * @brief Defines a render strategy that is defined by a sequence of
   *        textures
   * 
   */
  class GAMESDK_DLL SimpleSequenceRenderStrategy : public RenderStrategy {
  public:
    /**
     * @brief Constructs a new Simple Sequence Render Strategy
     * 
     * @param game the game
     * @param sequence the sequence of textures
     * @param frames the frames per texture
     * @param startAt the start frame
     * @param repeat wether sequence is repeated
     */
    SimpleSequenceRenderStrategy(GameBase* game, std::vector<sf::Texture*> sequence, int frames = 1, int startAt = 0, bool repeat = true);

    /**
     * @brief Destroys the Simple Sequence Render Strategy
     * 
     */
    virtual ~SimpleSequenceRenderStrategy();

    /**
     * @brief Wether the sequence is finished
     * 
     * @return bool sequence finished
     */
    virtual bool IsFinished();

    /**
     * @brief Sets the Size of a texture
     * 
     * @param idx texture index
     * @param size the new size
     */
    virtual void SetSize(int idx, sf::Vector2f size);

    /**
     * @brief Sets the Size of all textures
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
    int mFrames = 1;
    int mCurIdx = 0;
    bool mRepeated = true;
    std::vector<sf::Sprite> mSequence;
    int mCurFrame = 0;
    bool mIsFinished = false;
  };
} // namespace game

#endif