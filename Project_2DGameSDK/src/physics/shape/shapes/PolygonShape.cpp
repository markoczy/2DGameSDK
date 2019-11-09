#include <2DGameSDK/physics/shape/shapes/PolygonShape.h>

namespace game {

  PolygonShape::PolygonShape(Game* game, std::vector<cpVect> vertices) : Shape(ShapeType::Polygon, game), mVertices(vertices) {
  }

  void PolygonShape::Render(sf::RenderTarget* target, sf::Color color, float stroke) {
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

  cpShape* PolygonShape::initShape(cpSpace*, cpBody* body) {
    auto shape = cpPolyShapeNewRaw(body, mVertices.size(), &mVertices[0], 0);
    return shape;
  }
} // namespace game
