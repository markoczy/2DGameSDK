#ifndef __POLYGON_KINEMATIC_SHAPE_H__
#define __POLYGON_KINEMATIC_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/PolygonShape.h>
#include <2DGameSDK/physics/shape/types/KinematicShape.h>

namespace game {
  class GAMESDK_DLL PolygonKinematicShape : public KinematicShape, public PolygonShape {
  public:
    PolygonKinematicShape(Game* game, std::vector<cpVect> vertices);
  };

} // namespace game

#endif