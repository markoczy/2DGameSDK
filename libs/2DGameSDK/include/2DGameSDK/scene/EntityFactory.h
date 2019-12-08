#ifndef __ENTITY_FACTORY_H__
#define __ENTITY_FACTORY_H__

#include <2DGameSDK/dll/gamesdk_dll.h>

#include <2DGameSDK/common/Constants.h>
#include <2DGameSDK/scene/entity/definitions/DynamicEntity.h>

namespace game {

  class GAMESDK_DLL EntityFactory {
  public:
    static DynamicEntity CreateSingleSpriteDynamicEntity(int type, GameBase* game, sf::Texture* texture, std::vector<Shape<DynamicShapeDefinition>*> shapes, sf::Vector2f size = constants::DIMENSION_USE_DEFAULT, bool isCollidable = false);

    static DynamicEntity CreateAnimatedDynamicEntity(int type, GameBase* game, sf::Texture* texture, std::vector<Shape<DynamicShapeDefinition>*> shapes, sf::Vector2f size = constants::DIMENSION_USE_DEFAULT, bool isCollidable = false);
  };

} // namespace game

#endif