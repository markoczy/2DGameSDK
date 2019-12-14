#include <2DGameSDK/event/observable/ObservableCounter.h>

namespace game {
  int ObservableCounter::observable_count = 0;

  int ObservableCounter::NextId() {
    return observable_count++;
  }

} // namespace game