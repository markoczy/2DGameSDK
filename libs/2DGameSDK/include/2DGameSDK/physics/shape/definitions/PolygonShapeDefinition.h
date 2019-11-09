#ifndef __POLYGON_SHAPE_DEFINITION_H__
#define __POLYGON_SHAPE_DEFINITION_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/ShapeType.h>

namespace game {

  class GAMESDK_DLL PolygonShapeDefinition : public Shape {
  public:
    PolygonShapeDefinition(Game* game, std::vector<cpVect> vertices);

    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5);

  protected:
    std::vector<cpVect> mVertices;

    virtual cpShape* initShape(cpSpace* space, cpBody* body);
  };
} // namespace game

#endif
