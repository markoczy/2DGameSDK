#include <2DGameSDK/event/EventController.h>

namespace game {

  EventController::EventController() {
  }

  EventController::~EventController() {
    for(auto it = mEvents.begin(); it != mEvents.end(); ++it) {
      helpers::safeDelete(it->second);
    }
    mEvents.clear();
  }

  void EventController::AddEvent(ObservableBase* event) {
    mEvents[event->GetId()] = event;
  }

  void EventController::DestroyEvent(ObservableBase* event) {
    mDestroyList.push_back(event->GetId());
  }

  void EventController::OnTick() {
    for(auto id : mDestroyList) {
      helpers::safeDelete(mEvents[id]);
      mEvents.erase(id);
    }
    mDestroyList.clear();

    for(auto it = mEvents.begin(); it != mEvents.end(); ++it) {
      it->second->Update();
    }
  }

} // namespace game