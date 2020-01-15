#include <2DGameSDK/core/projectile/prefabs/SequencedProjectile.h>

namespace game {
  SequencedProjectile::SequencedProjectile(GameBase* game, int type, std::vector<sf::Texture*> sequence, Shape<KinematicShapePhysics>* shapes, sf::Transform start, sf::Vector2f velocity, int maxLifetime, int seqFrames, int seqStart) : Projectile(game, type, new SimpleSequenceRenderStrategy(game, sequence, seqFrames, seqStart), shapes, start, velocity, maxLifetime) {}
} // namespace game
