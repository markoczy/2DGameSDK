#include "event/observer/FunctionObserver.h"

namespace game {

  template <class TData>
  FunctionObserver<TData>::FunctionObserver(ObserverFunc<TData> func) : mFunc(func) {
  }

  template <class TData>
  void FunctionObserver<TData>::Callback(TData* data) {
    mFunc(data);
  }

} // namespace game