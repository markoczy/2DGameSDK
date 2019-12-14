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
    virtual void Run() = 0;

    virtual void Stop() = 0;

    virtual GameOptions GetOptions() = 0;

    virtual sf::RenderWindow* GetWindow() = 0;

    virtual StateManagerBase* GetStateManager() = 0;

    virtual SceneGraph* GetScene() = 0;

    virtual GameWorld* GetWorld() = 0;

    virtual PoseConverter* GetPoseConverter() = 0;

    virtual CameraController* GetCameraController() = 0;

    virtual OverlayDisplay* GetOverlayDisplay() = 0;

    virtual AudioController* GetAudioController() = 0;

    virtual void SetOptions(GameOptions options) = 0;

    virtual void SetScene(SceneGraph* scene) = 0;

    virtual void SetWorld(GameWorld* world) = 0;

    virtual void AddEvent(ObservableBase* event) = 0;

    virtual void DestroyEvent(ObservableBase* event) = 0;

    virtual cpSpace* GetPhysicalWorld() = 0;
  };
} // namespace game

#endif