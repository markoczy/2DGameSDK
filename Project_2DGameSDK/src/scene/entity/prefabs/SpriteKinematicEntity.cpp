#include <2DGameSDK/scene/entity/prefabs/SpriteKinematicEntity.h>

namespace game {

  SpriteKinematicEntity::SpriteKinematicEntity(int type, GameBase* game, sf::Texture* texture, std::vector<Shape<KinematicShapePhysics>*> shapes, bool isCollidable) : KinematicEntity(type, game, nullptr, shapes, isCollidable) {
    mSpriteRenderer = new SingleSpriteRenderStrategy(game, texture);
    mRenderer = mSpriteRenderer;
  }

  void SpriteKinematicEntity::SetSize(sf::Vector2f size) {
    mSpriteRenderer->SetSize(size);
  }
} // namespace game