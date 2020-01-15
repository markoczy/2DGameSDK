/**
 * @file OverlayDisplay.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief OverlayDisplay class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __OVERLAY_DISPLAY_H__
#define __OVERLAY_DISPLAY_H__

#include <map>

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  /**
   * @brief Fully configuruable Overlay Display to display the status to the 
   * player
   * 
   */
  class GAMESDK_DLL OverlayDisplay {
  public:
    /**
     * @brief Constructs a new Overlay Display
     * 
     * @param game the game
     */
    OverlayDisplay(GameBase* game);

    /**
     * @brief Adds a new Drawable element
     * 
     * @param elem the element
     * @param enabled wether the element is enabled at start
     * @return int the element id
     */
    int AddElement(sf::Drawable* elem, bool enabled = true);

    /**
     * @brief Forces update when a drawable was changed
     * 
     */
    void Update();

    /**
     * @brief Enables an element by id
     * 
     * @param id the element id
     */
    void Enable(int id);

    /**
     * @brief Disables an element by id
     * 
     * @param id 
     */
    void Disable(int id);

    /**
     * @brief Updates the Overlay Display
     * 
     */
    void OnTick();

    /**
     * @brief Renders the Overlay Display
     * 
     * @param target the render target
     */
    void OnRender(sf::RenderTarget* target);

  private:
    GameBase* mGame = nullptr;
    std::map<int, std::tuple<sf::Drawable*, bool>> mDrawables;
    bool mStateChanged = true;
    sf::RenderTexture* mTexture;
    sf::Sprite mSprite;
    sf::Mutex mRenderMutex;
  };

} // namespace game

#endif