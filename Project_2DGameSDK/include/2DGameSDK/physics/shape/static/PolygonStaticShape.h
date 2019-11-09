#ifndef __POLYGON_STATIC_SHAPE_H__
#define __POLYGON_STATIC_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/StaticShape.h>
#include <2DGameSDK/physics/shape/shapes/PolygonShape.h>

namespace game {
  class GAMESDK_DLL PolygonStaticShape : public StaticShape, public PolygonShape {
  public:
    PolygonStaticShape(Game* game, std::vector<cpVect> vertices, bool isSensor = false);
  };

} // namespace game

#endif