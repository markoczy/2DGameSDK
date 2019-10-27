#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;
using namespace game::constants;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  using namespace helpers;

  SpriteTransformableEntity::SpriteTransformableEntity(int type, Game* game, sf::Texture* texture, bool isCollidable) : TransformableEntity(type, game, isCollidable), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mShape = cpBoxShapeNew(mBody, rect.width, rect.height, 0);
    cpSpaceAddShape(game->GetPhysicalWorld(), mShape);
    cpShapeSetCollisionType(mShape, CollisionType::Default);
    cpShapeSetSensor(mShape, true);
    mSprite.setOrigin(rect.width / 2, rect.height / 2);
  }

  SpriteTransformableEntity::SpriteTransformableEntity(int type, Game* game, sf::Texture* texture, std::vector<sf::Vector2f>) : TransformableEntity(type, game, true), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mShape = cpBoxShapeNew(mBody, rect.width, rect.height, 0);
    cpSpaceAddShape(game->GetPhysicalWorld(), mShape);
    cpShapeSetCollisionType(mShape, CollisionType::Default);
    cpShapeSetSensor(mShape, true);
    mSprite.setOrigin(rect.width / 2, rect.height / 2);
  }

  SpriteTransformableEntity::~SpriteTransformableEntity() {
  }

  void SpriteTransformableEntity::OnTick() {}

  int rot = 0;

  void SpriteTransformableEntity::OnTickEnded() {
    auto worldHeight = getGame()->GetWorld()->GetBounds().height;
    auto localOrigin = GetCombinedTransform().transformPoint(sf::Vector2f());
    auto localXUnit = GetCombinedTransform().transformPoint(sf::Vector2f(1, 0));
    auto localDir = localXUnit - localOrigin;
    auto physicalOrigin = GrahicTools::GetPhysicalPos(localOrigin, worldHeight);

    float angle = -atan2(localDir.y, localDir.x);

    LOGD("Body Pos: (" << physicalOrigin.x << ", " << physicalOrigin.y << "), angle: " << angle);
    cpBodySetPosition(mBody, physicalOrigin);
    cpBodySetAngle(mBody, angle);

    if(getGame()->GetOptions().RenderAABB) updateAABB();
    if(getGame()->GetOptions().RenderCollisionMask) updateCollisionMask();
  }

  void SpriteTransformableEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform = states.transform * mCombinedTransform;
    target->draw(mSprite, states);
  }

  sf::FloatRect SpriteTransformableEntity::GetAABB() {
    return mAABB;
  }

  std::vector<sf::Vector2f> SpriteTransformableEntity::GetCollisionMask() {
    return mTransformedCollisionMask;
  }

  void SpriteTransformableEntity::updateAABB() {
    auto bb = cpShapeCacheBB(mShape);
    auto worldHeight = getGame()->GetWorld()->GetBounds().height;

    auto topLeftVis = GrahicTools::GetVisualPos(cpv(bb.l, bb.t), worldHeight);
    auto bottomRightVis = GrahicTools::GetVisualPos(cpv(bb.r, bb.b), worldHeight);
    mAABB = sf::FloatRect(topLeftVis.x,
                          topLeftVis.y,
                          bottomRightVis.x - topLeftVis.x,
                          bottomRightVis.y - topLeftVis.y);

    LOGD("bb.l: " << bb.l << ", bb.t: " << bb.t << ", bb.r - bb.l: " << bb.r - bb.l << ", bb.t - bb.b: " << bb.t - bb.b);
    LOGD("mAABB.l: " << mAABB.left << ", mAABB.t: " << mAABB.top << ", mAABB.width: " << mAABB.width << ", mAABB.height: " << mAABB.height);
  }

  void SpriteTransformableEntity::updateCollisionMask() {
    auto worldHeight = getGame()->GetWorld()->GetBounds().height;
    auto physOrigin = cpBodyGetPosition(mBody);
    auto visOrigin = GrahicTools::GetVisualPos(physOrigin, worldHeight);

    float w = mSprite.getTextureRect().width;
    float h = mSprite.getTextureRect().height;

    // Handle Rotation
    auto rotRad = cpBodyGetAngle(mBody);
    float rot = -(360 * rotRad) / 6.28;
    auto rotTransform = sf::Transform().rotate(rot, visOrigin);

    mTransformedCollisionMask = std::vector<sf::Vector2f>();
    mTransformedCollisionMask.push_back(rotTransform.transformPoint(sf::Vector2f(visOrigin.x - w / 2, visOrigin.y - h / 2)));
    mTransformedCollisionMask.push_back(rotTransform.transformPoint(sf::Vector2f(visOrigin.x + w / 2, visOrigin.y - h / 2)));
    mTransformedCollisionMask.push_back(rotTransform.transformPoint(sf::Vector2f(visOrigin.x + w / 2, visOrigin.y + h / 2)));
    mTransformedCollisionMask.push_back(rotTransform.transformPoint(sf::Vector2f(visOrigin.x - w / 2, visOrigin.y + h / 2)));
  }

  void SpriteTransformableEntity::onEntityTransformed() {
    mTransformationOccured = true;
  }

} // namespace game