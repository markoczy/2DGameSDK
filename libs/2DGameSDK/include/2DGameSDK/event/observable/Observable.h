#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/observable/ObservableBase.h>
#include <2DGameSDK/event/observer/Observer.h>
#include <iostream>
#include <vector>

namespace game {

  template <class TData>
  class Observable : public ObservableBase {
  public:
    struct TriggerData {
      bool Triggered;
      TData* Data;
    };
    // void Emit(TData* data);
    void Subscribe(Observer<TData>* subscriber) {
      // void Subscribe(Observer<TData> subscriber) {
      mObservers.push_back(subscriber);
      std::cout << "Observer length: " << mObservers.size() << std::endl;
    }

    virtual void Update() {
      bool trigger = false;
      auto data = triggered();

      if(data.Triggered) {
        for(Observer<TData>* iObs : mObservers) {
          // LOGD("Emitting Callback...");
          iObs->Callback(data.Data);
        }
      }
    }

  protected:
    // TODO isocpp: avoid out parameters
    virtual TriggerData triggered() = 0;

  private:
    std::vector<Observer<TData>*> mObservers;
  };

} // namespace game

#endif