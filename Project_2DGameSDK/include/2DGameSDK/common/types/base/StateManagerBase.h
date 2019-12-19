#ifndef __STATE_MANAGER_BASE_H__
#define __STATE_MANAGER_BASE_H__

#include <SFML/Graphics.hpp>

namespace game {
  class GameWorld;
  class SceneGraph;
  class GameObject;
  class VisualObject;

  class StateManagerBase {
  public:
    virtual GameWorld* GetWorld() = 0;

    virtual SceneGraph* GetScene() = 0;

    virtual GameObject* GetObject(int id) = 0;

    virtual sf::Mutex* GetRenderMutex() = 0;

    virtual void SetWorld(GameWorld* world) = 0;

    virtual void SetScene(SceneGraph* scene) = 0;

    virtual void AddObject(GameObject* object) = 0;

    virtual void AddVisualObject(VisualObject* object) = 0;

    virtual void DestroyObject(GameObject* object) = 0;

    virtual void DestroyVisualObject(VisualObject* object) = 0;

    virtual void OnTick() = 0;

    virtual void OnTickEnded() = 0;

    virtual void OnRender(sf::RenderTarget* target) = 0;

    virtual void OnZOrderChanged() = 0;
  };

} // namespace game

#endif