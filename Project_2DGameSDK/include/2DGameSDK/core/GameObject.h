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

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/ObjectType.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/common/types/base/StateManagerBase.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

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
    GameObject(ObjectType objType, GameBase* game);

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

    ObjectType GetObjectType();

    virtual void OnTick();

    virtual void OnTickEnded();

  protected:
    GameBase* getGame();

  private:
    ObjectType mObjectType = ObjectType::Unknown;
    int mId = 0;
    GameBase* mGame = nullptr;
    int mZIndex = 0;
  };

} // namespace game

#endif