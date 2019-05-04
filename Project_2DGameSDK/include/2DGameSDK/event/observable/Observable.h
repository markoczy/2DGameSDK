#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/observable/ObservableBase.h>
#include <2DGameSDK/event/observer/Observer.h>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>

namespace game {

  template <class TData>
  class Observable : public ObservableBase {
  public:
    // void Emit(TData* data);
    int Subscribe(Observer<TData>* subscriber) {
      // void Subscribe(Observer<TData> subscriber) {
      // mObservers.push_back(subscriber);
      int id = mCounter;
      mObservers[id] = subscriber;
      mCounter++;
      return id;
    }

    void Unsubscribe(int id) {
      mObservers.erase(id);
    }

    virtual void Update() {
      bool trigger = false;
      auto data = triggered();

      if(std::get<0>(data)) {
        for(auto const& iObs : mObservers) {
          iObs.second->Callback(std::get<1>(data));
        }
      }
    }

  protected:
    virtual std::tuple<bool, TData*> triggered() = 0;

  private:
    std::map<int, Observer<TData>*> mObservers;
    // std::vector<Observer<TData>*> mObservers;
    int mCounter;
  };

} // namespace game

#endif