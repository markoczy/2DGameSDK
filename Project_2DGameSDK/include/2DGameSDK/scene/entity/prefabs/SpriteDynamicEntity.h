#ifndef __SPRITE_DYNAMIC_ENTITY_H__
#define __SPRITE_DYNAMIC_ENTITY_H__

#include <2DGameSDK/core/visual/SingleSpriteRenderStrategy.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/scene/entity/definitions/DynamicEntity.h>

namespace game {

  class GAMESDK_DLL SpriteDynamicEntity : public DynamicEntity {
  public:
    SpriteDynamicEntity(int type,
                        GameBase* game,
                        sf::Texture* texture,
                        std::vector<Shape<DynamicShapeDefinition>*> shapes = std::vector<Shape<DynamicShapeDefinition>*>(),
                        bool isCollidable = false);

    void SetSize(sf::Vector2f size);

  private:
    SingleSpriteRenderStrategy* mSpecificRenderer = nullptr;
  };

} // namespace game

#endif
