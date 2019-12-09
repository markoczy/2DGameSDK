#ifndef __SEQUENCED_PROJECTILE_H__
#define __SEQUENCED_PROJECTILE_H__

#include <2DGameSDK/core/projectile/Projectile.h>
#include <2DGameSDK/core/visual/SimpleSequenceRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  class GAMESDK_DLL SequencedProjectile : public Projectile {
  public:
    SequencedProjectile(GameBase* game, int type, std::vector<sf::Texture*> sequence, Shape<KinematicShapeDefinition>* shapes, sf::Transform start, sf::Vector2f velocity, int seqFrames = 1, int seqStart = 0);
  };

} // namespace game

#endif