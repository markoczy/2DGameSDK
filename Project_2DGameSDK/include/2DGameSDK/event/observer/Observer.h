#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  template <class TData>
  class Observer {
  public:
    Observer() {}
    virtual void Callback(TData* data){};
  };

} // namespace game

#endif