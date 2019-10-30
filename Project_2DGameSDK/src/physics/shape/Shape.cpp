#include <2DGameSDK/physics/shape/Shape.h>

namespace game {

  Shape::Shape(ShapeType type, Game* game) : mType(type), mGame(game) {}

  void Shape::AttachToBody(cpSpace* space, cpBody* body) {
    mSpace = space;
    mBody = body;

    mShape = initShape(space, body);
  }

  ShapeType Shape::GetType() {
    return mType;
  }

  cpSpace* Shape::GetRefSpace() {
    return mSpace;
  }

  cpBody* Shape::GetRefBody() {
    return mBody;
  }

  cpShape* Shape::GetRefShape() {
    return mShape;
  }

  Game* Shape::getGame() {
    return mGame;
  }

  sf::Vector2f Shape::getVisualPosition() {
    auto converter = getGame()->GetPointConverter();
    auto physOrigin = cpBodyGetPosition(mBody);
    return converter->GetVisualPos(physOrigin);
  }

  float Shape::getVisualRotation() {
    auto rotRad = cpBodyGetAngle(mBody);
    return -(360 * rotRad) / 6.28;
  }

} // namespace game