/**
 * @file Observable.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Observable class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __OBSERVABLE_H__
#define __OBSERVABLE_H__

#include <iostream>
#include <map>
#include <tuple>
#include <vector>

#include <2DGameSDK/common/Helpers.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/observable/ObservableBase.h>
#include <2DGameSDK/event/observable/ObservableCounter.h>
#include <2DGameSDK/event/observer/Observer.h>

namespace game {

  /**
   * @brief Generic Observable type, used to create Game Events
   * 
   * @tparam TData The type of data to emit from the Observable
   * 
   */
  template <class TData>
  class Observable : public ObservableBase {
  public:
    /**
     * @brief Constructs a new Observable
     * 
     */
    Observable() : mId(ObservableCounter::NextId()) {
    }

    /**
     * @brief Destroys the Observable
     * 
     */
    virtual ~Observable() {
      for(auto entry : mObservers) {
        helpers::safeDelete(entry.second);
      }
    }

    /**
     * @brief Retreives the Id
     * 
     * @return int the id
     */
    virtual int GetId() {
      return mId;
    }

    /**
     * @brief Register an Observer for this Observable.
     * 
     * @param subscriber The Observer
     * 
     * @return The unique subscription id
     */
    int Subscribe(Observer<TData>* subscriber) {
      int id = mCounter;
      mObservers[id] = subscriber;
      mCounter++;
      return id;
    }

    /**
     * @brief Unregister an Observer by it's unique subscription id.
     * 
     * @param id The unique subscription id
     */
    void Unsubscribe(int id) {
      mObservers.erase(id);
    }

    /**
     * @brief Updates the observable i.e. verifies if the observable was
     *        triggered. If triggered, the callback function of all registered
     *        Observers is executed.
     * 
     */
    virtual void Update() {
      auto data = triggered();

      if(std::get<0>(data)) {
        for(auto const& iObs : mObservers) {
          iObs.second->Callback(std::get<1>(data));
        }
      }
    }

  protected:
    /**
     * @brief Abstract function that checks if the Observable was triggered.
     * 
     * @return A tuple that specifies wether the event was triggered (value 0)
     *         and optionally contains the trigger data (value 1).
     */
    virtual std::tuple<bool, TData> triggered() = 0;

  private:
    std::map<int, Observer<TData>*> mObservers;
    int mId = 0;
    int mCounter = 0;

    static int observable_counter;
  };

} // namespace game

#endif