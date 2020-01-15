/**
 * @file Effect.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Effect class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/types/ObjectType.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/GameObject.h>
#include <2DGameSDK/core/VisualObject.h>
#include <2DGameSDK/core/state/StateManager.h>
#include <2DGameSDK/core/visual/SimpleSequenceRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  /**
   * @brief Animation effect defined by a sequence of textures
   * 
   */
  class GAMESDK_DLL Effect : public GameObject, public VisualObject {
  public:
    /**
     * @brief Constructs a new Effect
     * 
     * @param game the game
     * @param sequence the sequence of textures
     * @param transform the transformation of the render pose
     * @param framesPerSprite time to render each texture
     */
    Effect(GameBase* game, std::vector<sf::Texture*> sequence, sf::Transform transform = sf::Transform::Identity, int framesPerSprite = 1);

    /**
     * @brief Destroys the Effect
     * 
     */
    virtual ~Effect();

    /**
     * @brief Retreives the Z Index
     * 
     * @return int the z index
     */
    virtual int GetZIndex();

    /**
     * @brief Sets the Z Index
     * 
     * @param zIndex the new Z Index
     */
    virtual void SetZIndex(int zIndex);

    /**
     * @brief Sets the Transform
     * 
     * @param transform the new Transform
     */
    virtual void SetTransform(sf::Transform transform);

    /**
     * @brief Sets the Size
     * 
     * @param size the new size
     */
    virtual void SetSize(sf::Vector2f size);

    /**
     * @brief Sets the Size for a single texture
     * 
     * @param idx the texture id
     * @param size the new size
     */
    virtual void SetSize(int idx, sf::Vector2f size);

    /**
     * @brief Updates the Effect
     * 
     */
    virtual void OnTick();

    /**
     * @brief Renders the Effect
     * 
     * @param target the render target
     * @param states the render states
     */
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

  protected:
    SimpleSequenceRenderStrategy* mRenderer = nullptr;
    sf::Transform mTransform;
    int mZIndex = constants::DEFAULT_ZINDEX_EFFECT;

    void onDestroy();
  };
} // namespace game

#endif