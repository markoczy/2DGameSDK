#include <2DGameSDK/core/state/StateManager.h>

namespace game {

  StateManager::StateManager(GameBase* game) : mGame(game), mRenderMutex(new sf::Mutex()) {
  }

  StateManager::~StateManager() {
    helpers::safeDelete(mRenderMutex);
  }

  GameWorld* StateManager::GetWorld() {
    return mWorld;
  }

  SceneGraph* StateManager::GetScene() {
    return mScene;
  }

  sf::Mutex* StateManager::GetRenderMutex() {
    return mRenderMutex;
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
    LOGD("Adding Object " << object->GetId() << " of Type: " << (int)object->GetObjectType() << ", size now: " << mRenderObjects.size());
  }

  void StateManager::AddVisualObject(VisualObject* object) {
    mRenderObjects.push_back(object);
    OnZOrderChanged();
  }

  void StateManager::DestroyObject(GameObject* object) {
    mDestroyObjects.push_back(object->GetId());
  }

  void StateManager::DestroyVisualObject(VisualObject* object) {
    auto it = std::find(mRenderObjects.begin(), mRenderObjects.end(), object);
    if(it != mRenderObjects.end()) {
      mRenderObjects.erase(it);
    }
  }

  void StateManager::OnTick() {
    auto lock = sf::Lock(*mRenderMutex);
    for(auto entry : mObjects) {
      entry.second->OnTick();
    }

    auto overlay = mGame->GetOverlayDisplay();
    if(overlay != nullptr) overlay->OnTick();
  }

  void StateManager::OnTickEnded() {
    auto lock = sf::Lock(*mRenderMutex);
    for(auto id : mDestroyObjects) {
      helpers::safeDelete(mObjects[id]);
      mObjects.erase(id);
    }
    mDestroyObjects.clear();

    for(auto entry : mObjects) {
      entry.second->OnTickEnded();
    }
  }

  void StateManager::OnRender(sf::RenderTarget* target) {
    auto lock = sf::Lock(*mRenderMutex);
    int cnt = 0;
    for(auto iObj : mRenderObjects) {
      if(iObj != nullptr) {
        iObj->OnRender(target);
        cnt++;
      }
    }

    auto overlay = mGame->GetOverlayDisplay();
    if(overlay != nullptr) overlay->OnRender(target);
    LOGD("Statemanager Rendered " << cnt << " Objects");
  }

  void StateManager::OnZOrderChanged() {
    std::sort(mRenderObjects.begin(), mRenderObjects.end(), VisualObject::SortByZOrder);
  }

} // namespace game
