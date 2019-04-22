#ifndef __EVENT_CONTROLLER_H__
#define __EVENT_CONTROLLER_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/observable/ObservableBase.h>
#include <map>
#include <string>

namespace game {

  class GAMESDK_DLL EventController {
  public:
    EventController();
    ~EventController();

    int AddEvent(ObservableBase* event);
    ObservableBase* GetEvent(int id);

    void Tick();

  private:
    int mEventCounter = 0;
    std::map<int, ObservableBase*> mEvents;
  };

} // namespace game

#endif