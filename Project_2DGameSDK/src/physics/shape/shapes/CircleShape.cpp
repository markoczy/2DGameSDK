#include <2DGameSDK/physics/shape/shapes/CircleShape.h>

namespace game {

  CircleShape::CircleShape(Game* game, float radius, cpVect offset) : Shape(ShapeType::Polygon, game), mRadius(radius), mOffset(offset) {
  }

  void CircleShape::Render(sf::RenderTarget* target, sf::Color color, float stroke) {
    auto shape = sf::CircleShape(mRadius);
    shape.setOrigin(sf::Vector2f(mRadius, mRadius));
    shape.setPosition(getVisualPosition());
    shape.setRotation(getVisualRotation());
    shape.setOutlineColor(color);
    shape.setOutlineThickness(stroke);
    shape.setFillColor(sf::Color::Transparent);
    target->draw(shape);
  }

  cpShape* CircleShape::initShape(cpSpace*, cpBody* body) {
    auto shape = cpCircleShapeNew(body, mRadius, mOffset);
    return shape;
  }
} // namespace game
