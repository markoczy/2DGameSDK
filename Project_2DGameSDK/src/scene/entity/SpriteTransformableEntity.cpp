#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode {
  public:
    sf::Transform GetAccumulatedTransform();
  };

  SpriteTransformableEntity::SpriteTransformableEntity(int type, sf::Texture* texture) : TransformableEntity(type), mSprite(*texture) {
    mCollisionMask = helpers::GrahicTools::GetRectBoundary(mSprite.getLocalBounds());
  }

  SpriteTransformableEntity::SpriteTransformableEntity(int type, sf::Texture* texture, std::vector<sf::Vector2f> collisionMask) : TransformableEntity(type, true), mSprite(*texture) {
    mCollisionMask = collisionMask;
  }

  SpriteTransformableEntity::~SpriteTransformableEntity() {
  }

  void SpriteTransformableEntity::Tick() {}

  void SpriteTransformableEntity::Render(sf::RenderTarget* target, sf::RenderStates states) {
    //* Note: The render states contain the accumulated transformation
    target->draw(mSprite, states);
  }

  sf::Transformable* SpriteTransformableEntity::GetTransformable() {
    return &mSprite;
  }

  sf::FloatRect SpriteTransformableEntity::GetAABB() {
    return (mGraphNode->GetAccumulatedTransform() * mSprite.getTransform()).transformRect(mSprite.getLocalBounds());
  }

  std::vector<sf::Vector2f> SpriteTransformableEntity::GetCollisionMask() {
    auto localToWorld = mGraphNode->GetAccumulatedTransform() * mSprite.getTransform();

    return helpers::GrahicTools::TransformPoints(mCollisionMask, localToWorld);
  }

} // namespace game