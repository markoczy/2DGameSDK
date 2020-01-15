/**
 * @file ObservableCounter.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief ObservableCounter class
 * @version 1.0
 * @date 2020-01-15
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef __OBSERVABLE_COUNTER_H__
#define __OBSERVABLE_COUNTER_H__

#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  /**
   * @brief Static counter for observables
   * 
   */
  class GAMESDK_DLL ObservableCounter {
  public:
    /**
     * @brief Retreives the next id
     * 
     * @return int the next id
     */
    static int NextId();

  private:
    static int observable_count;
  };
} // namespace game

#endif