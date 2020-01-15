#include <2DGameSDK/scene/entity/prefabs/SpriteDynamicEntity.h>

namespace game {

  SpriteDynamicEntity::SpriteDynamicEntity(int type, GameBase* game, sf::Texture* texture, std::vector<Shape<DynamicShapePhysics>*> shapes, bool isCollidable) : DynamicEntity(type, game, nullptr, shapes, isCollidable) {
    mSpecificRenderer = new SingleSpriteRenderStrategy(game, texture);
    mRenderer = mSpecificRenderer;
  }

  void SpriteDynamicEntity::SetSize(sf::Vector2f size) {
    mSpecificRenderer->SetSize(size);
  }
} // namespace game