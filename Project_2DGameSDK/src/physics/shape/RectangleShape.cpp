#include <2DGameSDK/physics/shape/RectangleShape.h>

namespace game {
  std::vector<sf::Vector2f> initPoints(float width, float height) {
    float w2 = width / 2;
    float h2 = height / 2;
    auto ret = std::vector<sf::Vector2f>();
    ret.push_back(sf::Vector2f(-w2, -h2));
    ret.push_back(sf::Vector2f(w2, -h2));
    ret.push_back(sf::Vector2f(w2, h2));
    ret.push_back(sf::Vector2f(-w2, h2));
    return ret;
  }

  RectangleShape::RectangleShape(float width, float height) : Shape(ShapeType::Rectangle), mWidth(width), mHeight(height) {}

  cpShape* RectangleShape::initShape(cpSpace* space, cpBody* body) {
    auto shape = cpBoxShapeNew(getRefBody(), mWidth, mHeight, 0);
    cpSpaceAddShape(space, shape);
    cpShapeSetCollisionType(shape, CollisionType::Default);
    cpShapeSetSensor(shape, true);
    return shape;
  }

  sf::Shape* RectangleShape::GetDrawableShape(PointConverter* converter) {
    auto body = getRefBody();
    auto physOrigin = cpBodyGetPosition(body);
    auto visOrigin = converter->GetVisualPos(physOrigin);

    auto rotRad = cpBodyGetAngle(body);
    float rot = -(360 * rotRad) / 6.28;
    auto transform = sf::Transform().translate(visOrigin).rotate(rot, visOrigin);
    auto s = sf::RectangleShape();
  }

} // namespace game
