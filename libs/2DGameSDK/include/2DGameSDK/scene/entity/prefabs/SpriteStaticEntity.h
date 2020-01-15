#ifndef __SPRITE_STATIC_ENTITY_H__
#define __SPRITE_STATIC_ENTITY_H__

#include <2DGameSDK/core/visual/SingleSpriteRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/definitions/StaticEntity.h>

namespace game {

  class GAMESDK_DLL SpriteStaticEntity : public StaticEntity {
  public:
    SpriteStaticEntity(int type,
                       GameBase* game,
                       sf::Texture* texture,
                       std::vector<Shape<StaticShapePhysics>*> shapes = std::vector<Shape<StaticShapePhysics>*>(),
                       bool isCollidable = false);

    void SetSize(sf::Vector2f size);

  private:
    SingleSpriteRenderStrategy* mSpecificRenderer = nullptr;
  };

} // namespace game

#endif
