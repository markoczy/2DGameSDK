#include <2DGameSDK/scene/entity/SpriteTransformableEntity.h>

using namespace sf;

namespace game {

  // SceneGraphNode forward Declaration
  class SceneGraphNode {
  public:
    sf::Transform GetAccumulatedTransform();
  };

  SpriteTransformableEntity::SpriteTransformableEntity(int type, sf::Texture* texture) : TransformableEntity(type) {
    mSprite = new Sprite(*texture);
  }

  SpriteTransformableEntity::~SpriteTransformableEntity() {
    delete mSprite;
  }

  void SpriteTransformableEntity::Tick() {}

  void SpriteTransformableEntity::Render(sf::RenderTarget* target) {
    auto states = RenderStates(mGraphNode->GetAccumulatedTransform());
    target->draw(*mSprite, states);
  }

  sf::Transformable* SpriteTransformableEntity::GetTransformable() {
    return mSprite;
  }

} // namespace game