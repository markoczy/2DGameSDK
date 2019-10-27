#include <2DGameSDK/physics/shape/Shape.h>

namespace game {

  Shape::Shape(ShapeType type) : mType(type) {}

  void Shape::AttachToBody(cpSpace* space, cpBody* body) {
    mSpace = space;
    mBody = body;

    mShape = initShape(space, body);
  }

  cpSpace* Shape::getRefSpace() {
    return mSpace;
  }

  cpBody* Shape::getRefBody() {
    return mBody;
  }

  cpShape* Shape::getRefShape() {
    return mShape;
  }

} // namespace game