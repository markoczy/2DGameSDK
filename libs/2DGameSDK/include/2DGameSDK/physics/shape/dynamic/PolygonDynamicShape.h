#ifndef __POLYGON_DYNAMIC_SHAPE_H__
#define __POLYGON_DYNAMIC_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/definitions/DynamicShape.h>
#include <2DGameSDK/physics/shape/shapes/PolygonShape.h>

namespace game {
  class GAMESDK_DLL PolygonDynamicShape : public DynamicShape, public PolygonShape {
  public:
    PolygonDynamicShape(Game* game, std::vector<cpVect> vertices);
  };

} // namespace game

#endif