#include <2DGameSDK/physics/shape/Shape.h>

namespace game {

  Shape::Shape(ShapeType type, Game* game, ShapeDefinition* definition) : mType(type), mGame(game), mDefinition(definition) {}

  void Shape::AttachToBody(cpSpace* space, cpBody* body) {
    mSpace = space;
    mBody = body;

    mShape = initShape(space, body);
    mDefinition->InitProperties(space, body, mShape);
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

    auto conv = getGame()->GetPoseConverter();
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
  }

  Game* Shape::getGame() {
    return mGame;
  }

  sf::Vector2f Shape::getVisualPosition() {
    auto converter = getGame()->GetPoseConverter();
    return converter->GetVisualPos(cpBodyGetPosition(mBody));
  }

  float Shape::getVisualRotation() {
    auto converter = getGame()->GetPoseConverter();
    return converter->GetVisualAngle(cpBodyGetAngle(mBody));
  }

} // namespace game