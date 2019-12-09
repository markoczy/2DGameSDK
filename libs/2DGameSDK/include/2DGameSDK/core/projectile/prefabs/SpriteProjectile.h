#ifndef __SPRITE_PROJECTILE_H__
#define __SPRITE_PROJECTILE_H__

#include <SFML/Graphics.hpp>

#include <2DGameSDK/common/types/base/GameBase.h>
#include <2DGameSDK/core/projectile/Projectile.h>
#include <2DGameSDK/core/visual/RenderStrategy.h>
#include <2DGameSDK/core/visual/SingleSpriteRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>

namespace game {

  class GAMESDK_DLL SpriteProjectile : public Projectile {
  public:
    SpriteProjectile(GameBase* game, int type, sf::Texture* texture, Shape<KinematicShapeDefinition>* shape, sf::Transform start, sf::Vector2f velocity);
  };
} // namespace game

#endif