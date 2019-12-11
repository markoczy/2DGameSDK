#include <2DGameSDK/core/state/StateManager.h>

namespace game {

  StateManager::StateManager(GameBase* game) : mGame(game) {
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
    for(auto it = mRenderObjects.begin(); it != mRenderObjects.end(); it++) {
      if(*it == object) {
        mRenderObjects.erase(it);
        return;
      }
    }
  }

  void StateManager::OnTick() {
    for(auto entry : mObjects) {
      entry.second->OnTick();
    }
  }

  void StateManager::OnTickEnded() {
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
    int cnt = 0;
    for(auto iObj : mRenderObjects) {
      if(iObj != nullptr) {
        iObj->OnRender(target);
        cnt++;
      }
    }

    // bool renderAABB = mGame->GetOptions().RenderAABB;
    // bool renderCollisionMasks = mGame->GetOptions().RenderCollisionMask;
    // if(renderAABB || renderCollisionMasks) {
    // }
    LOGD("Rendered " << cnt << " Objects");
  }

  void StateManager::OnZOrderChanged() {
    std::sort(mRenderObjects.begin(), mRenderObjects.end(), VisualObject::SortByZOrder);
  }

} // namespace game
