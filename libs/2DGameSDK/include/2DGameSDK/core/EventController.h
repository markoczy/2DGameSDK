#include <2DGameSDK/event/observable/ObservableBase.h>
#include <map>
#include <string>

namespace game {

  class EventController {
    static int eventId;

  public:
    EventController() {
      eventId = 0;
    }

    void AddEvent(int key, ObservableBase* event) {
      mEvents[eventId++] = event;
    }

    ObservableBase* GetEvent(int key) {
      return mEvents[key];
    }

    void Tick() {
      for(auto it = mEvents.begin(); it != mEvents.end(); ++it) {
        it->second->Update();
      }
    }

  private:
    std::map<int, ObservableBase*> mEvents;
  };

} // namespace game