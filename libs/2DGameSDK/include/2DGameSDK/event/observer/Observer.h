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
    ~Observer() {
      if(mSubscriptionId != -1) {
        mObservable->Unsubscribe(mSubscriptionId);
      }
    }

    virtual void Callback(TData* data){};
    void SubscribeTo(Observable<TData>* observable) {
      // TODO handle already subscibed
      mSubscriptionId = observable->Subscribe(this);
      mObservable = observable;
    }

  protected:
    int mSubscriptionId = -1;
    Observable<TData>* mObservable;
  };

} // namespace game

#endif