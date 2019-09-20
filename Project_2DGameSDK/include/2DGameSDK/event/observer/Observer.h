/**
 * @file Observer.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Observer class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  // Forward Declaration
  template <class TData>
  class Observable;

  /**
   * @brief Generic abstract Observer template of the Event implementation.
   * 
   * @tparam TData The type of Data that is emitted from the Observable
   */
  template <class TData>
  class Observer {
  public:
    /**
     * @brief Creates a new Observer
     * 
     */
    Observer() {}

    /**
     * @brief Destroys the Observer. Unregisters from Observable if the 
     *        Observable was registered with the SubscribeTo function.
     * 
     */
    virtual ~Observer() {
      if(mSubscriptionId != -1) {
        mObservable->Unsubscribe(mSubscriptionId);
      }
    }

    /**
     * @brief Abstract callback function to be executed when the Observable
     *        is triggered.
     * 
     * @param data The Data that is emitted from the Observable
     */
    virtual void Callback(TData* data) = 0;

    /**
     * @brief Subscribes the Observable to the given Observable and stores
     *        the subscription Id. Convenience function that is not fully 
     *        conform to the observable pattern (it's use is optional).
     * 
     * @param observable The Observable to Subscribe to
     */
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