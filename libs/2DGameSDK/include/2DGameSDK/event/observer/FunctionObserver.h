/**
 * @file FunctionObserver.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Function Observer class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __FUNCTION_OBSERVER_H__
#define __FUNCTION_OBSERVER_H__

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/event/observer/Observer.h>

namespace game {

  /**
   * @brief Template that defines a FunctionObserver Callback function.
   * 
   */
  template <class TData>
  using ObserverFunc = void (*)(TData*);

  /**
   * @brief Observer specialisation that uses a function as a callback.
   *        Does not have any scope or closure, if scope is needed, the
   *        MethodObserver class should be used.
   * 
   */
  template <class TData>
  class FunctionObserver : public Observer<TData> {
  public:
    /**
     * @brief Creates a FunctionObserver
     * 
     * @param func The Callback function
     */
    FunctionObserver(ObserverFunc<TData> func) : mFunc(func) {
    }

    /**
     * @brief Callback function that is called when the Observable triggers.
     * 
     * @param data The Data coming from the Observable.
     * 
     */
    void Callback(TData* data) {
      mFunc(data);
    }

  private:
    ObserverFunc<TData> mFunc;
  };

} // namespace game
#endif