#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  SpriteTransformableEntity::SpriteTransformableEntity(int type, Game* game, sf::Texture* texture) : TransformableEntity(type, game), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mShape = cpBoxShapeNew(mBody, rect.width, rect.height, 0);
    cpSpaceAddShape(game->GetPhysicalWorld(), mShape);
    // mCollisionMask = helpers::GrahicTools::GetRectBoundary(mSprite.getLocalBounds());
  }

  SpriteTransformableEntity::SpriteTransformableEntity(int type, Game* game, sf::Texture* texture, std::vector<sf::Vector2f> collisionMask) : TransformableEntity(type, game, true), mSprite(*texture) {
    // TODO
    auto rect = mSprite.getTextureRect();
    mShape = cpBoxShapeNew(mBody, rect.width, rect.height, 0);
    cpSpaceAddShape(game->GetPhysicalWorld(), mShape);
    // mCollisionMask = collisionMask;
  }

  SpriteTransformableEntity::~SpriteTransformableEntity() {
  }

  void SpriteTransformableEntity::OnTick() {}

  int rot = 0;

  void SpriteTransformableEntity::OnTickEnded() {
    auto w = mSprite.getTextureRect().width;
    auto h = mSprite.getTextureRect().height;

    auto origin = GetTransform().transformPoint(sf::Vector2f());
    auto xunit = GetTransform().transformPoint(sf::Vector2f(1, 0));
    auto dir = xunit - origin;
    float angle;
    if(dir.y == 1.0f) {
      angle = constants::PI_2;
    } else {
      angle = atan(dir.y / dir.x);
    }
    LOGD("Body Pos: (" << origin.x << ", " << origin.y << ")");
    LOGD("Body Dir: (" << dir.x << ", " << dir.y << "), angle: " << angle);
    cpBodySetPosition(mBody, cpv(origin.x + w / 2, origin.y - h / 2));
    cpBodySetAngle(mBody, angle);
    // cpBodySetAngle(mBody, GetTransform().

    // cpBodySetRot(mBody, cpv(pos.x, pos.y));
    // if(mTransformationOccured) {
    // updateAABB();
    // updateCollisionMask();
    // }0
  }

  void SpriteTransformableEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform = states.transform * mCombinedTransform;
    target->draw(mSprite, states);
  }

  sf::FloatRect SpriteTransformableEntity::GetAABB() {
    auto bb = cpShapeGetBB(mShape);
    // LOGD("bb.l: " << bb.l << ", bb.t: " << bb.t << ", bb.b: " << bb.b << ", bb.r: " << bb.r);
    LOGD("bb.l: " << bb.l << ", bb.t: " << bb.t << ", bb.r - bb.l: " << bb.r - bb.l << ", bb.t - bb.b: " << bb.t - bb.b);
    return sf::FloatRect(bb.l, bb.t, bb.r - bb.l, bb.t - bb.b);

    // updateAABB();
    // return sf::FloatRect();
  }

  // std::vector<sf::Vector2f> SpriteTransformableEntity::GetCollisionMask() {
  //   // return mTransformedCollisionMask;
  //   cpShapeget
  // }

  void SpriteTransformableEntity::updateAABB() {
    mAABB = mCombinedTransform.transformRect(mSprite.getLocalBounds());
  }

  void SpriteTransformableEntity::updateCollisionMask() {
    // mTransformedCollisionMask = helpers::GrahicTools::TransformPoints(mCollisionMask, mCombinedTransform);
  }

  void SpriteTransformableEntity::onEntityTransformed() {
    mTransformationOccured = true;
  }

} // namespace game