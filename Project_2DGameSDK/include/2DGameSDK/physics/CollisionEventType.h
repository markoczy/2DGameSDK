#ifndef __COLLSION_EVENT_TYPE_H__
#define __COLLSION_EVENT_TYPE_H__

namespace game {

  enum CollisionEventType {
    Begin,
    PreSolve,
    PostSolve,
    Separate
  };
}

#endif