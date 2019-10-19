#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  SpriteTransformableEntity::SpriteTransformableEntity(int type, Game* game, sf::Texture* texture) : TransformableEntity(type, game), mSprite(*texture) {
    mCollisionMask = helpers::GrahicTools::GetRectBoundary(mSprite.getLocalBounds());
  }

  SpriteTransformableEntity::SpriteTransformableEntity(int type, Game* game, sf::Texture* texture, std::vector<sf::Vector2f> collisionMask) : TransformableEntity(type, game, true), mSprite(*texture) {
    mCollisionMask = collisionMask;
  }

  SpriteTransformableEntity::~SpriteTransformableEntity() {
  }

  void SpriteTransformableEntity::OnTick() {}

  void SpriteTransformableEntity::OnTickEnded() {
    // if(mTransformationOccured) {
    updateAABB();
    updateCollisionMask();
    // }
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
    mAABB = mCombinedTransform.transformRect(mSprite.getLocalBounds());
  }

  void SpriteTransformableEntity::updateCollisionMask() {
    mTransformedCollisionMask = helpers::GrahicTools::TransformPoints(mCollisionMask, mCombinedTransform);
  }

  void SpriteTransformableEntity::onEntityTransformed() {
    mTransformationOccured = true;
  }

} // namespace game