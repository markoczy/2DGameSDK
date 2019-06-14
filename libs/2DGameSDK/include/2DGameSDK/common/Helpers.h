/**
 * @file Helpers.h
 * @author Aleistar Markoczy (a.markoczy@gmail.com)
 * @brief Common Helper functions for the 2DGameSDK
 * @version 1.0
 * @date 2019-06-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __GAMESDK_HELPERS_H__
#define __GAMESDK_HELPERS_H__

namespace game::helpers {

  template <class T>
  void safeDelete(T*& ptr) {
    if(ptr != nullptr) {
      delete ptr;
      ptr = nullptr;
    }
  }

} // namespace game::helpers

#endif