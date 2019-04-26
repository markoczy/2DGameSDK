#ifndef __OBSERVABLE_BASE_H__
#define __OBSERVABLE_BASE_H__

#include "2DGameSDK/gamesdk_dll.h"

namespace game {

  /**
 * @brief Parent class of any observable type
 */
  class GAMESDK_DLL ObservableBase {
  public:
    virtual void Update() = 0;
  };

} // namespace game

#endif