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
    StateManager(GameBase* game);
    ~StateManager();

    GameWorld* GetWorld();

    SceneGraph* GetScene();

    EventController* GetEventController();

    GameObject* GetObject(int id);

    sf::Mutex* GetRenderMutex();

    void SetWorld(GameWorld* world);

    void SetScene(SceneGraph* scene);

    void SetEventController(EventController* eventController);

    void AddObject(GameObject* object);

    void AddVisualObject(VisualObject* object);

    void DestroyObject(GameObject* object);

    void DestroyVisualObject(VisualObject* object);

    void OnTick();

    void OnTickEnded();

    void OnRender(sf::RenderTarget* target);

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
  };
} // namespace game

#endif