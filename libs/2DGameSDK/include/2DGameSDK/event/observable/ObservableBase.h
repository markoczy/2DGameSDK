/**
 * @file ObservableBase.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Observable Base class
 * @version 1.0
 * @date 2019-06-11
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __OBSERVABLE_BASE_H__
#define __OBSERVABLE_BASE_H__

#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  /**
   * @brief Base class of any observable type
   */
  class ObservableBase {
  public:
    virtual ~ObservableBase() {}

    /**
     * @brief Updates the observable i.e. verifies if the observable was
     *        triggered. If triggered, the callback function of all registered
     *        Observers is executed.
     * 
     */
    virtual void Update() = 0;
  };

} // namespace game

#endif