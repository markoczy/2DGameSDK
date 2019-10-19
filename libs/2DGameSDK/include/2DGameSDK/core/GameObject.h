/**
 * @file GameObject.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief GameObject class
 * @version 1.0
 * @date 2019-06-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <SFML/Graphics.hpp>

namespace game {

  /**
   * @brief Defines a simple Game Object (no transformations)
   * 
   * @see TransformableGameObject
   * 
   */
  class GAMESDK_DLL GameObject {
  public:
    /**
     * @brief Creates a new GameObject
     * 
     * @param type The GameObject Type (does not affect anything and is meant
     *        to be used freely to identify entities of some kind)
     */
    GameObject(int type, int zIndex = 0);

    /**
     * @brief Destroys the GameObject
     * 
     */
    ~GameObject();

    /**
     * @brief Retreives the Id
     * 
     * @return int The Identifier
     */
    int GetId();

    /**
     * @brief Retreives the Type
     * 
     * @return int The GameObject Type
     */
    int GetType();

    int GetZIndex();

    /**
     * @brief Updates the GameObject
     * 
     */
    virtual void OnTick() = 0;

    /**
     * @brief Renders the GameObject
     * 
     * @param target The screen or texture to render on
     * @param states The initial Render States (transformation etc.)
     */
    virtual void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default) = 0;

  protected:
    int mType;
    int mId;
    int mZIndex;
  };

} // namespace game

#endif