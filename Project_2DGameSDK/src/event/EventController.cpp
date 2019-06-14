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

  int EventController::AddEvent(ObservableBase* event) {
    mEvents[mEventCounter] = event;
    return mEventCounter++;
  }

  ObservableBase* EventController::GetEvent(int id) {
    return mEvents[id];
  }

  void EventController::Tick() {
    for(auto it = mEvents.begin(); it != mEvents.end(); ++it) {
      it->second->Update();
    }
  }

} // namespace game