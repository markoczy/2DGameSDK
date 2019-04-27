#ifndef __OBSERVABLE_BASE_H__
#define __OBSERVABLE_BASE_H__

#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  /**
 * @brief Parent class of any observable type
 */
  class ObservableBase {
  public:
    virtual void Update() = 0;
  };

} // namespace game

#endif