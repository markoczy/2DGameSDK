#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;
using namespace game::constants;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  using namespace helpers;

  SpriteTransformableEntity::SpriteTransformableEntity(int type, Game* game, sf::Texture* texture, bool isCollidable) : TransformableEntity(type, game, isCollidable), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);

    auto shape = new RectangleSensorShape(getGame(), rect.width, rect.height);
    shape->AttachToBody(getGame()->GetPhysicalWorld(), mBody);
    mShapes.push_back(shape);
  }

  SpriteTransformableEntity::SpriteTransformableEntity(int type, Game* game, sf::Texture* texture, std::vector<Shape*> shapes) : TransformableEntity(type, game, true), mSprite(*texture) {
    auto rect = mSprite.getTextureRect();
    mSprite.setOrigin(rect.width / 2, rect.height / 2);

    mShapes = shapes;
    auto space = getGame()->GetPhysicalWorld();
    for(auto shape : mShapes) {
      shape->AttachToBody(space, mBody);
    }
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

    // if(getGame()->GetOptions().RenderAABB) updateAABB();
    // if(getGame()->GetOptions().RenderCollisionMask) updateCollisionMask();
  }

  void SpriteTransformableEntity::OnRender(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform = states.transform * mCombinedTransform;
    target->draw(mSprite, states);

    auto options = getGame()->GetOptions();
    if(!(options.RenderCollisionMask || options.RenderAABB)) return;

    for(auto shape : mShapes) {
      if(options.RenderCollisionMask) shape->Render(target, sf::Color::Red, 0.5);
      if(options.RenderAABB) shape->RenderAABB(target, sf::Color::Magenta, 0.5);
    }
  }

  sf::FloatRect SpriteTransformableEntity::GetAABB() {
    return mAABB;
  }

  std::vector<sf::Vector2f> SpriteTransformableEntity::GetCollisionMask() {
    return mTransformedCollisionMask;
  }

  void SpriteTransformableEntity::updateAABB() {
    // TODO hardcoded
    auto bb = cpShapeCacheBB(mShapes[0]->GetRefShape());
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

  void SpriteTransformableEntity::onEntityTransformed() {
    mTransformationOccured = true;
  }

} // namespace game