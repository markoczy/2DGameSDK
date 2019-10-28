#include <2DGameSDK/physics/shape/RectangleShape.h>

namespace game {

  RectangleShape::RectangleShape(Game* game, float width, float height) : Shape(ShapeType::Rectangle, game), mWidth(width), mHeight(height) {}

  cpShape* RectangleShape::initShape(cpSpace* space, cpBody* body) {
    auto shape = cpBoxShapeNew(GetRefBody(), mWidth, mHeight, 0);
    cpSpaceAddShape(space, shape);
    cpShapeSetCollisionType(shape, CollisionType::Default);
    cpShapeSetSensor(shape, true);
    return shape;
  }

  void RectangleShape::Render(sf::RenderTarget* target, sf::Color color, float stroke) {
    auto converter = getGame()->GetPointConverter();
    auto body = GetRefBody();
    auto physOrigin = cpBodyGetPosition(body);
    auto visOrigin = converter->GetVisualPos(physOrigin);

    auto rotRad = cpBodyGetAngle(body);
    float rot = -(360 * rotRad) / 6.28;
    auto transform = sf::Transform().translate(visOrigin).rotate(rot, visOrigin);
    auto shape = sf::RectangleShape(sf::Vector2f(mWidth, mHeight));
    shape.setOrigin(mWidth / 2, mHeight / 2);
    shape.setPosition(visOrigin);
    shape.setRotation(rot);
    shape.setOutlineColor(color);
    shape.setOutlineThickness(stroke);
    shape.setFillColor(sf::Color::Transparent);
    target->draw(shape);
  }
} // namespace game
