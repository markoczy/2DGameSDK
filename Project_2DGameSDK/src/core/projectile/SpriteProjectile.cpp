#include <2DGameSDK/core/projectile/prefabs/SpriteProjectile.h>

namespace game {

  SpriteProjectile::SpriteProjectile(GameBase* game, int type, sf::Texture* texture, Shape<KinematicShapeDefinition>* shapes, sf::Transform start, sf::Vector2f velocity) : Projectile(game, type, new SingleSpriteRenderStrategy(game, texture), shapes, start, velocity) {}
} // namespace game
