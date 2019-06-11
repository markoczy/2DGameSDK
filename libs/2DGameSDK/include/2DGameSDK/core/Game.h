/**
 * @file Game.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Game class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __GAME_H__
#define __GAME_H__

#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/core/GameState.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/EventController.h>
#include <2DGameSDK/event/observable/ObservableBase.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chrono>
#include <iostream>
#include <thread>

namespace game {

  /**
   * @brief The Game is the main Controller of the 2DGameSDK, it is used
   *        to execute the main Game Loop, Process Events and Update/Render all
   *        Entities and the World.
   * 
   */
  class GAMESDK_DLL Game {
  public:
    /**
     * @brief Default empty constructor, Game is unusable until options,
     *        scene and world are set
     */
    Game();

    /**
     * @brief Full constructor, sets all needed objects to run the game
     * 
     */
    Game(GameOptions options, SceneGraph* scene, GameWorld* world);
    ~Game();

    /**
     * @brief Starts the Game
     * 
     */
    void Run();

    /**
     * @brief Stops the Game
     * 
     */
    void Stop();

    /**
     * @brief Returns a copy of the current game state
     * 
     * @return GameState the current state
     */
    GameState GetState();

    /**
     * @brief Retreives Reference of the SceneGraph
     * 
     * @return SceneGraph* The Scene Graph
     */
    SceneGraph* GetScene();

    /**
     * @brief Retreives the Reference of the world
     * 
     * @return GameWorld* The GameWorld
     */
    GameWorld* GetWorld();

    /**
     * @brief Assigns the Game Options
     * 
     * @param options The Game Options
     */
    void SetOptions(GameOptions options);

    /**
     * @brief Set the Scene object
     * 
     * @param scene the scene pointer
     * 
     * @remark Ownership of the object is tranfered to this class (i.e. object
     *         will be deleted when this class is out of scope)
     */
    void SetScene(SceneGraph* scene);

    /**
     * @brief Set the World object
     * 
     * @param world the world pointer
     * 
     * @remark Ownership of the object is tranfered to this class (i.e. object
     *         will be deleted when this class is out of scope)
     */
    void SetWorld(GameWorld* world);

    /**
     * @brief Add Event to watch inside the EventController
     * 
     * @param event the event to watch
     * 
     * @return int The Event identifier
     * 
     * @remark Ownership of the object is tranfered to this class (i.e. object
     *         will be deleted when this class is out of scope)
     */
    int AddEvent(ObservableBase* event);

    /**
     * @brief Get any Event from the EventController
     * 
     * @param id The Identifier
     * @return ObservableBase* The Event 
     */
    ObservableBase* GetEvent(int id);

  private:
    /**
     * @brief Updates all Game Elements
     * 
     */
    void tick();

    /**
     * @brief Renders all Game Elements
     * 
     */
    void render();

    EventController mEventCtrl;
    GameOptions mOptions;
    GameState mState;
    sf::RenderWindow* mWindow;
    sf::View mView;
  };
} // namespace game

#endif