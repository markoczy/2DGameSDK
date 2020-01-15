#ifndef __SPRITE_KINEMATIC_ENTITY_H__
#define __SPRITE_KINEMATIC_ENTITY_H__

#include <2DGameSDK/core/visual/SingleSpriteRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/definitions/KinematicEntity.h>

namespace game {

  class GAMESDK_DLL SpriteKinematicEntity : public KinematicEntity {
  public:
    SpriteKinematicEntity(int type,
                          GameBase* game,
                          sf::Texture* texture,
                          std::vector<Shape<KinematicShapePhysics>*> shapes = std::vector<Shape<KinematicShapePhysics>*>(),
                          bool isCollidable = false);

    void SetSize(sf::Vector2f size);

  protected:
    SingleSpriteRenderStrategy* mSpriteRenderer = nullptr;
  };

} // namespace game

#endif
