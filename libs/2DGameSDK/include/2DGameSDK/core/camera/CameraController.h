/**
 * @file CameraController.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief CameraController class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __CAMERA_CONTROLLER_H__
#define __CAMERA_CONTROLLER_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  class GAMESDK_DLL CameraController {
  public:
    /**
     * @brief Constructs a new Camera Controller
     * 
     * @param game the game
     */
    CameraController(GameBase* game);

    /**
     * @brief Destroys the Camera Controller
     * 
     */
    virtual ~CameraController();

    /**
     * @brief Retreives the current View
     * 
     * @return sf::View the view
     */
    virtual sf::View GetView() = 0;

    /**
     * @brief Retreives the camera Bounds
     * 
     * @return sf::Vector2f the camera bounds
     */
    virtual sf::Vector2f GetBounds() = 0;

    /**
     * @brief Sets the Zoom
     * 
     * @param zoom the new zoom
     */
    virtual void SetZoom(float zoom) = 0;

    /**
     * @brief Sets the Center
     * 
     * @param center the new center
     */
    virtual void SetCenter(sf::Vector2f center) = 0;

    /**
     * @brief Updates the Camera Controller
     * 
     */
    virtual void OnTick() = 0;

  protected:
    GameBase* getGame();

  private:
    GameBase* mGame;
  };

} // namespace game

#endif