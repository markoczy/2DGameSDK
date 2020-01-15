#ifndef __GAME_BASE_H__
#define __GAME_BASE_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

namespace game {
  class GameOptions;
  class StateManagerBase;
  class SceneGraph;
  class GameWorld;
  class PoseConverter;
  class ObservableBase;
  class OverlayDisplay;
  class AudioController;
  class CameraController;

  class GameBase {
  public:
    /**
     * @brief Runs the game
     * 
     */
    virtual void Run() = 0;

    /**
     * @brief Stops the game
     * 
     */
    virtual void Stop() = 0;

    /**
     * @brief Checks wether game is running
     * 
     * @return float game is running
     */
    virtual bool IsRunning() = 0;

    /**
     * @brief Retreives current game options
     * 
     * @return GameOptions the options
     */
    virtual GameOptions GetOptions() = 0;

    /**
     * @brief Retreives the game window
     * 
     * @return sf::RenderWindow* the window
     */
    virtual sf::RenderWindow* GetWindow() = 0;

    /**
     * @brief Retreives the current State Manager
     * 
     * @return StateManagerBase* the state manager
     */
    virtual StateManagerBase* GetStateManager() = 0;

    /**
     * @brief Retreives the current Scene Graph
     * 
     * @return SceneGraph* the Scene Graph
     */
    virtual SceneGraph* GetScene() = 0;

    /**
     * @brief Retreives the current GameWorld
     * 
     * @return GameWorld* the GameWorld
     */
    virtual GameWorld* GetWorld() = 0;

    /**
     * @brief Retreives the current Pose Converter
     * 
     * @return PoseConverter* the pose converter
     */
    virtual PoseConverter* GetPoseConverter() = 0;

    /**
     * @brief Retreives the current Camera Controller 
     * 
     * @return CameraController* the CameraController
     */
    virtual CameraController* GetCameraController() = 0;

    /**
     * @brief Retreives the current Overlay Display
     * 
     * @return OverlayDisplay* the overlay display 
     */
    virtual OverlayDisplay* GetOverlayDisplay() = 0;

    /**
     * @brief Retreives the current Audio Controller
     * 
     * @return AudioController* the audio controller
     */
    virtual AudioController* GetAudioController() = 0;

    /**
     * @brief Retreives the Chipmunk Physical World
     * 
     * @return cpSpace* the physical world
     */
    virtual cpSpace* GetPhysicalWorld() = 0;

    /**
     * @brief Sets the GameOptions
     * 
     * @param options the new options
     */
    virtual void SetOptions(GameOptions options) = 0;

    /**
     * @brief Sets the Scene
     * 
     * @param scene the new scene
     */
    virtual void SetScene(SceneGraph* scene) = 0;

    /**
     * @brief Sets the World
     * 
     * @param world the new world
     */
    virtual void SetWorld(GameWorld* world) = 0;

    /**
     * @brief Sends Event to EventController
     * 
     * @param event the new event
     */
    virtual void AddEvent(ObservableBase* event) = 0;

    /**
     * @brief Destroys event from EventController
     * 
     * @param event the event to destroy
     */
    virtual void DestroyEvent(ObservableBase* event) = 0;
  };
} // namespace game

#endif