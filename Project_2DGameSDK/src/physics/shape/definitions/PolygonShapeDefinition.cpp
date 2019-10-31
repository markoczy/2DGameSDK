#include <2DGameSDK/physics/shape/definitions/PolygonShapeDefinition.h>

namespace game {

  PolygonShapeDefinition::PolygonShapeDefinition(Game* game, std::vector<cpVect> vertices) : Shape(ShapeType::Polygon, game), mVertices(vertices) {
  }

  void PolygonShapeDefinition::Render(sf::RenderTarget* target, sf::Color color, float stroke) {
    auto shape = sf::ConvexShape(mVertices.size());
    for(size_t i = 0; i < mVertices.size(); i++) {
      shape.setPoint(i, sf::Vector2f(mVertices[i].x, -mVertices[i].y));
    }

    shape.setPosition(getVisualPosition());
    shape.setRotation(getVisualRotation());
    shape.setOutlineColor(color);
    shape.setOutlineThickness(stroke);
    shape.setFillColor(sf::Color::Transparent);
    target->draw(shape);
  }

  cpShape* PolygonShapeDefinition::initShape(cpSpace* space, cpBody* body) {
    auto shape = cpPolyShapeNewRaw(body, mVertices.size(), &mVertices[0], 0);
    cpSpaceAddShape(space, shape);
    cpShapeSetCollisionType(shape, CollisionType::Default);
    cpShapeSetSensor(shape, true);
    return shape;
  }
} // namespace game
