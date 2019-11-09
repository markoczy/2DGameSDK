#include <2DGameSDK/physics/shape/Shape.h>

namespace game {

  Shape::Shape(ShapeType type, Game* game) : mType(type), mGame(game) {}

  void Shape::AttachToBody(cpSpace* space, cpBody* body) {
    mSpace = space;
    mBody = body;

    mShape = initShape(space, body);
    initProperties(space, body, mShape);
    cpSpaceAddShape(space, mShape);
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

  void Shape::RenderAABB(sf::RenderTarget* target, sf::Color color, float stroke) {
    auto bb = cpShapeCacheBB(mShape);

    auto conv = getGame()->GetPointConverter();
    auto topLeftVis = conv->GetVisualPos(cpv(bb.l, bb.t));
    auto bottomRightVis = conv->GetVisualPos(cpv(bb.r, bb.b));
    auto visBB = sf::FloatRect(topLeftVis.x,
                               topLeftVis.y,
                               bottomRightVis.x - topLeftVis.x,
                               bottomRightVis.y - topLeftVis.y);

    auto rect = sf::RectangleShape(sf::Vector2f(visBB.width, visBB.height));
    rect.setPosition(visBB.left, visBB.top);
    rect.setOutlineColor(color);
    rect.setOutlineThickness(stroke);
    rect.setFillColor(sf::Color::Transparent);
    target->draw(rect);

    // LOGD("bb.l: " << bb.l << ", bb.t: " << bb.t << ", bb.r - bb.l: " << bb.r - bb.l << ", bb.t - bb.b: " << bb.t - bb.b);
    // LOGD("visBB.l: " << visBB.left << ", visBB.t: " << visBB.top << ", visBB.width: " << visBB.width << ", visBB.height: " << visBB.height);
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