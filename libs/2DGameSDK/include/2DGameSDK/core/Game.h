/**
 * @file Game.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Game class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __GAME_H__
#define __GAME_H__

#include <chrono>
#include <functional>
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
#include <2DGameSDK/core/audio/AudioController.h>
#include <2DGameSDK/core/camera/CameraController.h>
#include <2DGameSDK/core/camera/DefaultCameraController.h>
#include <2DGameSDK/core/projectile/Projectile.h>
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

    /**
     * @brief Checks wether game is running
     * 
     * @return float game is running
     */
    bool IsRunning();

    /**
     * @brief Retreives current game options
     * 
     * @return GameOptions the options
     */
    GameOptions GetOptions();

    /**
     * @brief Retreives the game window
     * 
     * @return sf::RenderWindow* the window
     */
    sf::RenderWindow* GetWindow();

    /**
     * @brief Retreives the current View
     * 
     * @return sf::View the view
     */
    sf::View GetView();

    /**
     * @brief Retreives the current State Manager
     * 
     * @return StateManagerBase* the state manager
     */
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

    /**
     * @brief Retreives the current Pose Converter
     * 
     * @return PoseConverter* the pose converter
     */
    PoseConverter* GetPoseConverter();

    /**
     * @brief Retreives the current Camera Controller 
     * 
     * @return CameraController* the CameraController
     */
    CameraController* GetCameraController();

    /**
     * @brief Retreives the current Overlay Display
     * 
     * @return OverlayDisplay* the overlay display 
     */
    OverlayDisplay* GetOverlayDisplay();

    /**
     * @brief Retreives the current Audio Controller
     * 
     * @return AudioController* the audio controller
     */
    AudioController* GetAudioController();

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
     * @brief Sets the Camera Controller
     * 
     * @param cameraController the new Camera Controller
     */
    void SetCameraController(CameraController* cameraController);

    /**
     * @brief Sets the Overlay Display
     * 
     * @param overlay the new Overlay display
     */
    void SetOverlayDisplay(OverlayDisplay* overlay);

    /**
     * @brief Resets camera controller to default
     * 
     */
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
    void AddEvent(ObservableBase* event);

    /**
     * @brief Destroys an event
     * 
     * @param event the event to destroy
     */
    void DestroyEvent(ObservableBase* event);

    /**
     * @brief Retreives the Chipmunk Physical World
     * 
     * @return cpSpace* the physical world
     */
    cpSpace* GetPhysicalWorld();

  private:
    /**
     * @brief Updates all Game Elements
     * 
     */
    void tick();

    StateManager mStateManager;
    GameOptions mOptions;

    bool mRunning = false;
    sf::RenderWindow* mWindow;
    sf::View mView;
    cpSpace* mPhysicalWorld = nullptr;
    PoseConverter* mPoseConverter = nullptr;
    CameraController* mCameraController = nullptr;
    CameraController* mDefaultCameraController = nullptr;
    OverlayDisplay* mOverlayDisplay = nullptr;
    AudioController* mAudioController = nullptr;
    sf::Thread* mRenderThread = nullptr;
  };
} // namespace game

#endif