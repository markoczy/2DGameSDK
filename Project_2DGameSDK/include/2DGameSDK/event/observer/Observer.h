#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  // Forward Declaration
  template <class TData>
  class Observable;

  template <class TData>
  class Observer {
  public:
    Observer() {}
    virtual void Callback(TData* data){};

  protected:
    int mSubscriptionId = -1;
    Observable<TData>* mObservable;
    // void SubscribeTo(Observable<TData> observable);
  };

} // namespace game

#endif