#include <2DGameSDK/core/state/StateManager.h>

namespace game {

  StateManager::StateManager() {
  }

  StateManager::~StateManager() {
  }

  GameWorld* StateManager::GetWorld() {
    return mWorld;
  }

  SceneGraph* StateManager::GetScene() {
    return mScene;
  }

  void StateManager::SetWorld(GameWorld* world) {
    mWorld = world;
  }

  void StateManager::SetScene(SceneGraph* scene) {
    mScene = scene;
  }

  GameObject* StateManager::GetObject(int id) {
    return mObjects[id];
  }

  void StateManager::AddObject(GameObject* object) {
    mObjects[object->GetId()] = object;
    mRenderObjects.push_back(object);
    LOGD("Adding Object " << object->GetId() << " of Type: " << (int)object->GetObjectType() << ", size now: " << mRenderObjects.size());
    OnZOrderChanged();
  }

  void StateManager::OnTick() {
    for(auto entry : mObjects) {
      entry.second->OnTick();
    }
  }

  void StateManager::OnTickEnded() {}

  void StateManager::OnRender(sf::RenderTarget* target) {
    int cnt = 0;
    for(auto iObj : mRenderObjects) {
      if(iObj != nullptr) {
        iObj->OnRender(target);
        cnt++;
      }
    }
    LOGD("Rendered " << cnt << " Objects");
  }

  void StateManager::OnZOrderChanged() {
    std::sort(mRenderObjects.begin(), mRenderObjects.end(), GameObject::SortByZOrder);
  }

} // namespace game
