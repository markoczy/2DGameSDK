#include <2DGameSDK/scene/entity/prefabs/SpriteStaticEntity.h>

namespace game {

  SpriteStaticEntity::SpriteStaticEntity(int type, GameBase* game, sf::Texture* texture, std::vector<Shape<StaticShapePhysics>*> shapes, bool isCollidable) : StaticEntity(type, game, nullptr, shapes, isCollidable) {
    mSpecificRenderer = new SingleSpriteRenderStrategy(game, texture);
    mRenderer = mSpecificRenderer;
  }

  void SpriteStaticEntity::SetSize(sf::Vector2f size) {
    mSpecificRenderer->SetSize(size);
  }
} // namespace game