#include "Event.h"
#include <string>

namespace game {

  class EventController {
  public:
    void Watch(std::string aId, Event* aEvent, void (*aOperation)(void));
    void Unwatch(std::string aId);
    void Tick();

  private:
    struct observer;
    std::vector<observer> mObservers;
  };

  struct EventController::observer {
    std::string Id;
    Event* Event;
    void (*Operation)(void);
  };

} // namespace game