#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode {
  public:
    sf::Transform GetAccumulatedTransform();
  };

  SpriteTransformableEntity::SpriteTransformableEntity(int type, sf::Texture* texture) : TransformableEntity(type), mSprite(*texture) {
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