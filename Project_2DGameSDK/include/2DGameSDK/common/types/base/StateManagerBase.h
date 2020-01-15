/**
 * @file StateManagerBase.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief StateManager Base Class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __STATE_MANAGER_BASE_H__
#define __STATE_MANAGER_BASE_H__

#include <SFML/Graphics.hpp>

namespace game {
  class GameWorld;
  class SceneGraph;
  class GameObject;
  class VisualObject;
  class EventController;

  class StateManagerBase {
  public:
    /**
     * @brief Retreives the current GameWorld
     * 
     * @return GameWorld* 
     */
    virtual GameWorld* GetWorld() = 0;

    /**
     * @brief Retreives the current Scene
     * 
     * @return SceneGraph* the Scene
     */
    virtual SceneGraph* GetScene() = 0;

    /**
     * @brief Retreives the current Event Controller
     * 
     * @return EventController* the EventController
     */
    virtual EventController* GetEventController() = 0;

    /**
     * @brief Retreives an Object by id
     * 
     * @param id the object id
     * @return GameObject* the GameObject
     */
    virtual GameObject* GetObject(int id) = 0;

    /**
     * @brief Retreives the current Render Mutex
     * 
     * @return sf::Mutex* the mutex
     */
    virtual sf::Mutex* GetRenderMutex() = 0;

    /**
     * @brief Sets the World
     * 
     * @param world the new world
     */
    virtual void SetWorld(GameWorld* world) = 0;

    /**
     * @brief Sets the Scene
     * 
     * @param scene the new scene
     */
    virtual void SetScene(SceneGraph* scene) = 0;

    /**
     * @brief Sets the Event Controller
     * 
     * @param eventController the new EventController
     */
    virtual void SetEventController(EventController* eventController) = 0;

    /**
     * @brief Adds a new Object
     * 
     * @param object the object
     */
    virtual void AddObject(GameObject* object) = 0;

    /**
     * @brief Adds a new VisualObject
     * 
     * @param object the visual object
     */
    virtual void AddVisualObject(VisualObject* object) = 0;

    /**
     * @brief Marks an object for deletion, is deleted on next tick
     * 
     * @param object the object
     */
    virtual void DestroyObject(GameObject* object) = 0;

    /**
     * @brief Destroys a visual object
     * 
     * @param object the VisualObject
     */
    virtual void DestroyVisualObject(VisualObject* object) = 0;

    /**
     * @brief Updates the StateManager
     * 
     */
    virtual void OnTick() = 0;

    /**
     * @brief Renders all VisualObjects
     * 
     * @param target the render target
     */
    virtual void OnRender(sf::RenderTarget* target) = 0;

    /**
     * @brief Updates Z Order after change
     * 
     */
    virtual void OnZOrderChanged() = 0;
  };

} // namespace game

#endif