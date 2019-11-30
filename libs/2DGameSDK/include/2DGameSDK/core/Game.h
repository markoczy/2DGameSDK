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

#include <chrono>
#include <iostream>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/common/graphics/PoseConverter.h>
#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/common/types/base/StateManagerBase.h>
#include <2DGameSDK/core/GameOptions.h>
#include <2DGameSDK/core/GameState.h>
#include <2DGameSDK/core/camera/CameraController.h>
#include <2DGameSDK/core/camera/DefaultCameraController.h>
// #include <2DGameSDK/core/overlay/OverlayDisplay.h>
#include <2DGameSDK/core/state/StateManager.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/EventController.h>
#include <2DGameSDK/event/observable/ObservableBase.h>
#include <2DGameSDK/physics/CollisionEventType.h>
#include <2DGameSDK/physics/CollisionTarget.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/scene/SceneGraph.h>
#include <2DGameSDK/scene/entity/Entity.h>
#include <2DGameSDK/world/GameWorld.h>

namespace game {
  class OverlayDisplay;

  /**
   * @brief The Game is the main Controller of the 2DGameSDK, it is used
   *        to execute the main Game Loop, Process Events and Update/Render all
   *        Entities and the World.
   * 
   */
  class GAMESDK_DLL Game : public GameBase {
  public:
    /**
     * @brief Default empty constructor, Game is unusable until options,
     *        scene and world are set
     */
    Game(GameOptions options);

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

    GameOptions GetOptions();

    sf::RenderWindow* GetWindow();

    StateManagerBase* GetStateManager();

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

    PoseConverter* GetPoseConverter();

    CameraController* GetCameraController();

    OverlayDisplay* GetOverlayDisplay();

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

    void SetCameraController(CameraController* cameraController);

    void SetOverlayDisplay(OverlayDisplay* overlay);

    void ResetCameraController();

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

    //? encapsulation of physical world?
    cpSpace* GetPhysicalWorld();

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

    StateManager mStateManager;
    GameOptions mOptions;
    EventController mEventCtrl;
    sf::RenderWindow* mWindow;
    sf::View mView;
    cpSpace* mPhysicalWorld = nullptr;
    PoseConverter* mPoseConverter = nullptr;
    CameraController* mCameraController = nullptr;
    CameraController* mDefaultCameraController = nullptr;
    OverlayDisplay* mOverlayDisplay = nullptr;
  };
} // namespace game

#endif