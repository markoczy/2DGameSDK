#include <2DGameSDK/scene/entity/prefabs/SpriteKinematicEntity.h>

namespace game {

  SpriteKinematicEntity::SpriteKinematicEntity(int type, GameBase* game, sf::Texture* texture, std::vector<Shape<KinematicShapeDefinition>*> shapes, bool isCollidable) : KinematicEntity(type, game, nullptr, shapes, isCollidable) {
    mSpecificRenderer = new SingleSpriteRenderStrategy(game, texture);
    mRenderer = mSpecificRenderer;
  }

  void SpriteKinematicEntity::SetSize(sf::Vector2f size) {
    mSpecificRenderer->SetSize(size);
  }
} // namespace game