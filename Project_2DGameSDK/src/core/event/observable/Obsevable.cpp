#include "event/observable/Observable.h"

namespace game {

  template <class TData>
  void Observable<TData>::Update() {
    bool trigger = false;
    TData data = triggered(&trigger);

    if(trigger) {
      for(Observer<TData>* iObs : mObservers) {
        std::cout << "Emitting Callback..." << std::endl;
        iObs->Callback(data);
      }
    }
  }

  template <class TData>
  void Observable<TData>::Subscribe(Observer<TData>* subscriber) {
    // void Subscribe(Observer<TData> subscriber) {
    mObservers.push_back(subscriber);
    std::cout << "Observer length: " << mObservers.size() << std::endl;
  }

} // namespace game