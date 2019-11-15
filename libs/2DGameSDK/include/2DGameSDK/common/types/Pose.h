#ifndef __POSE_H__
#define __POSE_H__

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

namespace game {

  template <class T>
  struct Pose {
    T origin;
    float angle;
  };

  // struct VisualPose : Pose<sf::Vector2f> {};

  // struct PhysicalPose : Pose<cpVect> {};

} // namespace game

#endif