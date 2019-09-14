#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode {
  public:
    sf::Transform GetAccumulatedTransform();
  };

  SpriteTransformableEntity::SpriteTransformableEntity(int type, sf::Texture* texture) : TransformableEntity(type), mSprite(*texture) {
    mCollisionMask = ConvexShape(4);
    auto localBounds = mSprite.getLocalBounds();
    mCollisionMask.setPoint(0, sf::Vector2f(localBounds.top, localBounds.left));
    mCollisionMask.setPoint(1, sf::Vector2f(localBounds.top, localBounds.left + localBounds.width));
    mCollisionMask.setPoint(2, sf::Vector2f(localBounds.top + localBounds.height, localBounds.left + localBounds.width));
    mCollisionMask.setPoint(3, sf::Vector2f(localBounds.top + localBounds.height, localBounds.left));
  }

  SpriteTransformableEntity::SpriteTransformableEntity(int type, sf::Texture* texture, std::vector<sf::Vector2f> collisionMask) : TransformableEntity(type), mSprite(*texture) {
    mCollisionMask = ConvexShape(collisionMask.size());
    for(int iPt = 0; iPt < collisionMask.size(); iPt++) {
      mCollisionMask.setPoint(iPt, collisionMask[iPt]);
    }
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

} // namespace game