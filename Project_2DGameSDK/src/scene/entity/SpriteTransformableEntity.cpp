#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  using namespace helpers;

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

    auto world = getGame()->GetWorld();
    auto worldBounds = sf::FloatRect(0, 0, world->GetBounds().width, world->GetBounds().height);
    auto localOrigin = GetTransform().transformPoint(sf::Vector2f());
    auto transform =
        GrahicTools::GetTransformVisualToPhysical(
            localOrigin, sf::FloatRect(0, 0, w, h), worldBounds);

    auto physicalOrigin = transform.transformPoint(sf::Vector2f());
    auto physicalXUnit = transform.transformPoint(sf::Vector2f(1, 0));
    auto physicalXDir = physicalXUnit - physicalOrigin;
    float angle;
    // ???
    if(physicalXDir.y == 1.0f) {
      angle = constants::PI_2;
    } else {
      angle = atan(physicalXDir.y / physicalXDir.x);
    }
    LOGD("Body Pos: (" << physicalOrigin.x << ", " << physicalOrigin.y << ")");
    LOGD("Body Dir: (" << physicalXDir.x << ", " << physicalXDir.y << "), angle: " << angle);
    cpBodySetPosition(mBody, cpv(physicalOrigin.x, physicalOrigin.y));
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

    // TODO duplicate code
    auto w = mSprite.getTextureRect().width;
    auto h = mSprite.getTextureRect().height;
    auto world = getGame()->GetWorld();
    auto worldBounds = sf::FloatRect(0, 0, world->GetBounds().width, world->GetBounds().height);
    auto localOrigin = GetTransform().transformPoint(sf::Vector2f());
    auto transform =
        GrahicTools::GetTransformPhysicalToVisual(
            localOrigin, sf::FloatRect(0, 0, w, h), worldBounds);

    auto visualBB = sf::FloatRect(bb.l, bb.t, bb.r - bb.l, bb.t - bb.b);
    visualBB = transform.transformRect(visualBB);

    // LOGD("bb.l: " << bb.l << ", bb.t: " << bb.t << ", bb.b: " << bb.b << ", bb.r: " << bb.r);
    LOGD("bb.l: " << bb.l << ", bb.t: " << bb.t << ", bb.r - bb.l: " << bb.r - bb.l << ", bb.t - bb.b: " << bb.t - bb.b);
    LOGD("visualBB.l: " << visualBB.left << ", visualBB.t: " << visualBB.top << ", visualBB.width: " << visualBB.width << ", visualBB.height: " << visualBB.height);
    return visualBB;

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