#include <2DGameSDK/physics/shape/definitions/RectangleShape.h>

namespace game {

  RectangleShape::RectangleShape(Game* game, float width, float height) : Shape(ShapeType::Rectangle, game), mWidth(width), mHeight(height) {
  }

  void RectangleShape::Render(sf::RenderTarget* target, sf::Color color, float stroke) {
    auto visOrigin = getVisualPosition();
    float rot = getVisualRotation();
    auto shape = sf::RectangleShape(sf::Vector2f(mWidth, mHeight));
    shape.setOrigin(mWidth / 2, mHeight / 2);
    shape.setPosition(visOrigin);
    shape.setRotation(rot);
    shape.setOutlineColor(color);
    shape.setOutlineThickness(stroke);
    shape.setFillColor(sf::Color::Transparent);
    target->draw(shape);
  }

  cpShape* RectangleShape::initShape(cpSpace*, cpBody* body) {
    auto shape = cpBoxShapeNew(body, mWidth, mHeight, 0);
    return shape;
  }

} // namespace game
