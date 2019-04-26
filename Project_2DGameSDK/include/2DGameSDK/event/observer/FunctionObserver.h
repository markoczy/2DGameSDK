#ifndef __FUNCTION_OBSERVER_H__
#define __FUNCTION_OBSERVER_H__

#include "2DGameSDK/event/observer/Observer.h"
#include "2DGameSDK/gamesdk_dll.h"

namespace game {

  template <class TData>
  using ObserverFunc = void (*)(TData*);

  template <class TData>
  class GAMESDK_DLL FunctionObserver : public Observer<TData> {
  public:
    FunctionObserver(ObserverFunc<TData> func);

    void Callback(TData* data);

  private:
    ObserverFunc<TData> mFunc;
  };

} // namespace game
#endif