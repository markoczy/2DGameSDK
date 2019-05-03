#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/observable/ObservableBase.h>
#include <2DGameSDK/event/observer/Observer.h>
#include <iostream>
#include <tuple>
#include <vector>

namespace game {

  template <class TData>
  class Observable : public ObservableBase {
  public:
    // void Emit(TData* data);
    void Subscribe(Observer<TData>* subscriber) {
      // void Subscribe(Observer<TData> subscriber) {
      mObservers.push_back(subscriber);
      std::cout << "Observer length: " << mObservers.size() << std::endl;
    }

    virtual void Update() {
      bool trigger = false;
      auto data = triggered();

      if(std::get<0>(data)) {
        for(Observer<TData>* iObs : mObservers) {
          std::cout << " Emitting Callback..." << std::endl;
          // LOGD("Emitting Callback...");
          iObs->Callback(std::get<1>(data));
        }
      }
    }

  protected:
    virtual std::tuple<bool, TData*> triggered() = 0;

  private:
    std::vector<Observer<TData>*> mObservers;
  };

} // namespace game

#endif