#ifndef __SPRITE_PHYSICAL_ENTITY_H__
#define __SPRITE_PHYSICAL_ENTITY_H__

#include <vector>

#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>

#include <2DGameSDK/core/Game.h>
#include <2DGameSDK/dll/gamesdk_dll.h>
#include <2DGameSDK/physics/shape/dynamic/RectangleDynamicShape.h>
#include <2DGameSDK/physics/shape/types/DynamicShape.h>
#include <2DGameSDK/scene/entity/physical/PhysicalEntity.h>

namespace game {

  class GAMESDK_DLL SpritePhysicalEntity : public PhysicalEntity {
  private:
  public:
    SpritePhysicalEntity(int type, Game* game, sf::Texture* texture, bool isCollidable = false);
    SpritePhysicalEntity(int type, Game* game, sf::Texture* texture, std::vector<DynamicShape*> shapes);
    ~SpritePhysicalEntity();

    void OnRender(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);

  protected:
    sf::Sprite mSprite;
    std::vector<DynamicShape*> mShapes;
  };

} // namespace game

#endif