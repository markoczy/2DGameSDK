#ifndef __POLYGON_SHAPE_H__
#define __POLYGON_SHAPE_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/CollisionType.h>
#include <2DGameSDK/physics/shape/Shape.h>
#include <2DGameSDK/physics/shape/ShapeType.h>
#include <2DGameSDK/physics/shape/definitions/ShapeDefinition.h>

namespace game {

  template <class TDefinition>
  class GAMESDK_DLL PolygonShape : public Shape<TDefinition> {
  public:
    PolygonShape(Game* game, TDefinition* definition, std::vector<cpVect> vertices) : Shape<TDefinition>(ShapeType::Polygon, game, definition), mVertices(vertices) {}

    virtual void Render(sf::RenderTarget* target, sf::Color color = sf::Color::Black, float stroke = 0.5) {
      auto shape = sf::ConvexShape(mVertices.size());
      for(size_t i = 0; i < mVertices.size(); i++) {
        shape.setPoint(i, sf::Vector2f(mVertices[i].x, -mVertices[i].y));
      }

      shape.setPosition(Shape<TDefinition>::getVisualPosition());
      shape.setRotation(Shape<TDefinition>::getVisualRotation());
      shape.setOutlineColor(color);
      shape.setOutlineThickness(stroke);
      shape.setFillColor(sf::Color::Transparent);
      target->draw(shape);
    }

  protected:
    std::vector<cpVect> mVertices;

    virtual cpShape* initShape(cpSpace*, cpBody* body) {
      auto shape = cpPolyShapeNewRaw(body, mVertices.size(), &mVertices[0], 0);
      return shape;
    }
  };
} // namespace game

#endif
