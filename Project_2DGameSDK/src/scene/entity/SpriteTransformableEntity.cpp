#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode;

  SpriteTransformableEntity::SpriteTransformableEntity(int type, sf::Texture* texture) : TransformableEntity(type), mSprite(*texture) {
    mCollisionMask = helpers::GrahicTools::GetRectBoundary(mSprite.getLocalBounds());
  }

  SpriteTransformableEntity::SpriteTransformableEntity(int type, sf::Texture* texture, std::vector<sf::Vector2f> collisionMask) : TransformableEntity(type, true), mSprite(*texture) {
    mCollisionMask = collisionMask;
  }

  SpriteTransformableEntity::~SpriteTransformableEntity() {
  }

  void SpriteTransformableEntity::Tick() {}

  void SpriteTransformableEntity::OnTickEnded() {
    if(mTransformationOccured) {
      updateAABB();
      updateCollisionMask();
    }
  }

  void SpriteTransformableEntity::Render(sf::RenderTarget* target, sf::RenderStates states) {
    states.transform = states.transform * mFullTransform;
    target->draw(mSprite, states);
  }

  sf::FloatRect SpriteTransformableEntity::GetAABB() {
    return mAABB;
  }

  std::vector<sf::Vector2f> SpriteTransformableEntity::GetCollisionMask() {
    return mTransformedCollisionMask;
  }

  void SpriteTransformableEntity::updateAABB() {
    mAABB = mFullTransform.transformRect(mSprite.getLocalBounds());
  }

  void SpriteTransformableEntity::updateCollisionMask() {
    mTransformedCollisionMask = helpers::GrahicTools::TransformPoints(mCollisionMask, mFullTransform);
  }

  void SpriteTransformableEntity::onEntityTransformed() {
    mTransformationOccured = true;
  }

} // namespace game