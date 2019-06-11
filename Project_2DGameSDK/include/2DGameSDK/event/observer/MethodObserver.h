/**
 * @file MethodObserver.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Method Observer class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __METHOD_OBSERVER_H__
#define __METHOD_OBSERVER_H__

#include <2DGameSDK/event/observer/Observer.h>
#include <functional>

namespace game {
  /**
   * @brief Template that defines a MethodObserver Callback function.
   * 
   */
  template <class TData, class TCallee>
  using ObserverMethod = void (TCallee::*)(TData*);

  /**
   * @brief Observer specialisation that uses a given method of a given class 
   *        as a callback. Used to call functions in a specific class scope as 
   *        opposed to the FunctionObserver class that has no scope.
   * 
   */
  template <class TData, class TCallee>
  class MethodObserver : public Observer<TData> {
  public:
    /**
     * @brief Creates a Method Observer
     * 
     * @param callee The Class to call when the Observable triggers
     * @param func The Method of the specified class to call when the 
     *             Observable triggers
     * 
     */
    MethodObserver(TCallee* callee, ObserverMethod<TData, TCallee> func) : mCallee(callee), mFunc(func) {
    }

    /**
     * @brief Callback function that is called when the Observable triggers.
     * 
     * @param data The Data coming from the Observable.
     * 
     */
    void Callback(TData* data) {
      std::invoke(mFunc, mCallee, data);
    }

  private:
    TCallee* mCallee;
    ObserverMethod<TData, TCallee> mFunc;
  };

} // namespace game

#endif