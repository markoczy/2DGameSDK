#ifndef __FUNCTION_OBSERVER_H__
#define __FUNCTION_OBSERVER_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/observer/Observer.h>

namespace game {

  template <class TData>
  using ObserverFunc = void (*)(TData*);

  template <class TData>
  class FunctionObserver : public Observer<TData> {
  public:
    FunctionObserver(ObserverFunc<TData> func) : mFunc(func) {
    }

    void Callback(TData* data) {
      mFunc(data);
    }

  private:
    ObserverFunc<TData> mFunc;
  };

} // namespace game
#endif