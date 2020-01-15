/**
 * @file StateManager.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief StateManager class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __STATE_MANAGER_H__
#define __STATE_MANAGER_H__

#include <algorithm>
#include <map>

#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/common/types/base/StateManagerBase.h>
#include <2DGameSDK/core/GameObject.h>
#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/core/VisualObject.h>
#include <2DGameSDK/core/camera/CameraController.h>
#include <2DGameSDK/core/overlay/OverlayDisplay.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/EventController.h>
#include <2DGameSDK/scene/entity/Entity.h>

namespace game {
  class SceneGraph;
  class GameWorld;

  class StateManager : public StateManagerBase {
  public:
    /**
     * @brief Constructs a new State Manager
     * 
     * @param game the game
     */
    StateManager(GameBase* game);

    /**
     * @brief Destroys the State Manager
     * 
     */
    ~StateManager();

    /**
     * @brief Retreives the current GameWorld
     * 
     * @return GameWorld* 
     */
    GameWorld* GetWorld();

    /**
     * @brief Retreives the current Scene
     * 
     * @return SceneGraph* the Scene
     */
    SceneGraph* GetScene();

    /**
     * @brief Retreives the current Event Controller
     * 
     * @return EventController* the EventController
     */
    EventController* GetEventController();

    /**
     * @brief Retreives an Object by id
     * 
     * @param id the object id
     * @return GameObject* the GameObject
     */
    GameObject* GetObject(int id);

    /**
     * @brief Retreives the current Render Mutex
     * 
     * @return sf::Mutex* the mutex
     */
    sf::Mutex* GetRenderMutex();

    /**
     * @brief Sets the World
     * 
     * @param world the new world
     */
    void SetWorld(GameWorld* world);

    /**
     * @brief Sets the Scene
     * 
     * @param scene the new scene
     */
    void SetScene(SceneGraph* scene);

    /**
     * @brief Sets the Event Controller
     * 
     * @param eventController the new EventController
     */
    void SetEventController(EventController* eventController);

    /**
     * @brief Adds a new Object
     * 
     * @param object the object
     */
    void AddObject(GameObject* object);

    /**
     * @brief Adds a new VisualObject
     * 
     * @param object the visual object
     */
    void AddVisualObject(VisualObject* object);

    /**
     * @brief Marks an object for deletion, is deleted on next tick
     * 
     * @param object the object
     */
    void DestroyObject(GameObject* object);

    /**
     * @brief Destroys a visual object
     * 
     * @param object the VisualObject
     */
    void DestroyVisualObject(VisualObject* object);

    /**
     * @brief Updates the StateManager
     * 
     */
    void OnTick();

    /**
     * @brief Renders all VisualObjects
     * 
     * @param target the render target
     */
    void OnRender(sf::RenderTarget* target);

    /**
     * @brief Updates Z Order after change
     * 
     */
    void OnZOrderChanged();

  private:
    GameBase* mGame = nullptr;
    sf::Mutex* mRenderMutex = nullptr;

    GameWorld* mWorld = nullptr;
    SceneGraph* mScene = nullptr;
    EventController* mEventController = nullptr;
    std::map<int, GameObject*> mObjects;
    std::vector<VisualObject*> mRenderObjects;

    std::vector<int> mDestroyObjects;

    void onTick();
    void onTickEnded();
  };
} // namespace game

#endif