#ifndef __METHOD_OBSERVER_H__
#define __METHOD_OBSERVER_H__

#include <2DGameSDK/event/observer/Observer.h>
#include <functional>

namespace game {

  template <class TData, class TCallee>
  using ObserverMethod = void (TCallee::*)(TData*);

  // Method observer: Calls Function in class TCallee
  template <class TData, class TCallee>
  class MethodObserver : public Observer<TData> {
  public:
    MethodObserver(TCallee* callee, ObserverMethod<TData, TCallee> func) : mCallee(callee), mFunc(func) {
    }

    void Callback(TData* data) {
      std::invoke(mFunc, mCallee, data);
    }

  private:
    TCallee* mCallee;
    ObserverMethod<TData, TCallee> mFunc;
  };

} // namespace game

#endif