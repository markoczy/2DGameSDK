#ifndef __OBSERVABLE_COUNTER_H__
#define __OBSERVABLE_COUNTER_H__

#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {
  class GAMESDK_DLL ObservableCounter {
  public:
    static int NextId();

  private:
    static int observable_count;
  };
} // namespace game

#endif