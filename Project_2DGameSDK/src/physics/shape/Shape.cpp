#include <2DGameSDK/physics/shape/Shape.h>

namespace game {

  Shape::Shape(ShapeType type) : mType(type) {}

  void Shape::AttachToBody(cpSpace* space, cpBody* body) {
    mSpace = space;
    mBody = body;

    mShape = initShape(space, body);
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

} // namespace game